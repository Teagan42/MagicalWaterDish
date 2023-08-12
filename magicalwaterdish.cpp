/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/tglenn/src/particle/MagicalWaterDish/magicalwaterdish.ino"
// This #include statement was automatically added by the Particle IDE.

#include "Watering/WaterIntakeBox.h"
#include "Cleaning/CleaningSystem.h"
#include <numbers>
#include <vector>

void setup();
void loop();
#line 8 "/Users/tglenn/src/particle/MagicalWaterDish/magicalwaterdish.ino"
#define WATERING_INTAKE_VALVE_PIN D4
#define WATERING_LOW_WATER_PIN D7
#define WATERING_MED_WATER_PIN D6
#define WATERING_HIGH_WATER_PIN D5
#define WATERING_FILTER_SENSOR_PIN D8

#define CLEANING_DRAIN_SERVO_PIN D2
#define CLEANING_INJECTION_PUMP_PIN D1
#define CLEANING_INTAKE_VALVE_PIN D0

void openIntakeValve();
void closeIntakeValve();

Drain servoDrain(CLEANING_DRAIN_SERVO_PIN);
InjectionPump injectionPump(CLEANING_INJECTION_PUMP_PIN, PinState::HIGH);
IntakeValve cleaningIntakeVale(CLEANING_INTAKE_VALVE_PIN, PinState::HIGH);
CleaningCycle cycle5 = {
    .cycle = Cleaning::Cycle::DONE,
    .duration = 1000,
    .next = nullptr
};
CleaningCycle cycle4 = {
    .cycle = Cleaning::Cycle::RINSE,
    .duration = 15000,
    .next = &cycle5
};
CleaningCycle cycle3 = {
    .cycle = Cleaning::Cycle::SOAK,
    .duration = 10000,
    .next = &cycle4
};
CleaningCycle cycle2 = {
    .cycle = Cleaning::Cycle::WASH,
    .duration = 10000,
    .next = &cycle3
};
CleaningCycle cycle1 = {
    .cycle = Cleaning::Cycle::DRAIN,
    .duration = 30000,
    .next = &cycle2
};

CleaningCycle cycles[] = {cycle1, cycle2, cycle3, cycle4, cycle5};

CleaningSystem cleaningSystem(
    &cleaningIntakeVale,
    &injectionPump,
    cycles,
    &servoDrain,
    1
);

Trigger fallingCloseValve = {
    .interruptMode = InterruptMode::FALLING,
    .interrupt = &closeIntakeValve
};

Trigger fallingOpenValve = {
    .interruptMode = InterruptMode::FALLING,
    .interrupt = &openIntakeValve
};

WaterIntakeSensor highWater = {
    .pin = WATERING_HIGH_WATER_PIN,
    .pinMode = INPUT_PULLDOWN,
    .waterLevel = 80,
    .trigger = &fallingCloseValve
};

WaterIntakeSensor medWater = {
    .pin = WATERING_MED_WATER_PIN,
    .pinMode = INPUT_PULLDOWN,
    .waterLevel = 50,
};

WaterIntakeSensor lowWater = {
    .pin = WATERING_LOW_WATER_PIN,
    .pinMode = INPUT_PULLDOWN,
    .waterLevel = 20,
    .trigger = &fallingOpenValve
};



IntakeValve valveInlet(WATERING_INTAKE_VALVE_PIN, PinState::HIGH);
WaterIntakeSensor sensorInlets[] = {highWater, medWater, lowWater};
WaterIntakeBox box(&valveInlet, sensorInlets, 3); 

void openIntakeValve() {
    box.openValve();
}

void closeIntakeValve() {
    box.closeValve();
}

void setup() {
    cleaningSystem.setup();
    box.setup();
    box.activate();
}

void loop() {
    cleaningSystem.loop();
    box.loop();
    delay(100);
}