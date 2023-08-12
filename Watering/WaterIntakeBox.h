#ifndef LIB_WATER_INTAKE_H
#define LIB_WATER_INTAKE_H

#include <Arduino.h>
#include <vector>
#include "../Common/IntakeValve.h"

struct Valve {
    enum Action {
        NONE,
        OPEN,
        CLOSE
    };
};

struct Pin {
    enum State {
        IGNORE,
        HIGH,
        LOW
    };
};

struct Trigger {
    const InterruptMode interruptMode;
    void(*interrupt)();
};


struct WaterIntakeSensor {
    const int pin;
    const PinMode pinMode;
    const int waterLevel;
    Trigger* trigger = nullptr;
    int32_t lastState = 0;
};

class WaterIntakeBox {
protected:
    std::vector<WaterIntakeSensor*> _sensors;
    unsigned int _sensorCount;
    int _waterLevel;
    IntakeValve* _intakeValve;
    bool _isActive;
    void getCurrentWaterLevel();
public:
    WaterIntakeBox(IntakeValve*, WaterIntakeSensor*, int);
    void closeValve();
    void openValve();
    void setup();
    void loop();
    void activate();
    void deactivate();
    int getWaterLevel();
};

#endif