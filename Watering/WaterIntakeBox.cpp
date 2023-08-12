#include "WaterIntakeBox.h"

template<typename T>
std::vector<T*> toVector(T* array, int length) {
    return { array, array + length};
};

WaterIntakeBox::WaterIntakeBox(IntakeValve *valve, WaterIntakeSensor *sensors, int count)
{
    Serial.println("Water Intake Box : Initializing");
    _intakeValve = valve;
    _sensors = toVector(sensors, count);
    std::sort(_sensors.begin(), _sensors.end(), [](WaterIntakeSensor* a, WaterIntakeSensor* b) {
        return a->waterLevel < b->waterLevel;
    });
    _sensorCount = count;
    for(unsigned int i = 0; i < _sensors.size(); i++) {
        Serial.printlnf("Sensor with pin %d, and water level %d is index %d", _sensors[i]->pin, _sensors[i]->waterLevel, i);
    }
};

void WaterIntakeBox::closeValve() {
    Serial.println("Water Intake Box : Close Valve");
    _intakeValve->close();
};

void WaterIntakeBox::openValve() {
    Serial.println("Water Intake Box : Open Valve");
    if (!WaterIntakeBox::_isActive) {
        Serial.println("Water Intake Box: Disabled");
        return;
    }
    _intakeValve->open();
};

int WaterIntakeBox::getWaterLevel() {
    return _waterLevel;
};

void WaterIntakeBox::activate() {
    Serial.println("Water Intake Box : Activate");
    if (this->_isActive) {
        return;
    }
    this->_isActive = true;
    this->getCurrentWaterLevel();
};

void WaterIntakeBox::deactivate() {
    Serial.println("Water Intake Box : Deactivate");
    this->_isActive = false;
    this->_intakeValve->close();
};

void WaterIntakeBox::getCurrentWaterLevel() {
    int waterLevel = 0;
    for (unsigned int i = 0; i < _sensorCount; i++)
    {
        int32_t reading = digitalRead(_sensors[i]->pin);
        if (reading && _sensors.at(i)->waterLevel >= waterLevel) {
            waterLevel = _sensors.at(i)->waterLevel;
        }
        _sensors.at(i)->lastState = reading;
    }
    this->_waterLevel = waterLevel;
};

void WaterIntakeBox::setup() {
    Serial.println("Water Intake Box : Setup");
    for (unsigned int i = 0; i < _sensorCount; i++)
    {
        const WaterIntakeSensor *sensor = _sensors.at(i);
        pinMode(sensor->pin, sensor->pinMode);
        Trigger* trigger = _sensors.at(i)->trigger;
        if (!trigger->interrupt || !trigger->interruptMode) {
            continue;
        }
        attachInterrupt(sensor->pin, *trigger->interrupt, trigger->interruptMode);
    }
    this->getCurrentWaterLevel();
};

void WaterIntakeBox::loop() {
    Serial.println("Water Intake Box : Loop");
    this->getCurrentWaterLevel();
};