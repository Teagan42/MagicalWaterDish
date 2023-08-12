#include "IntakeValve.h"

IntakeValve::IntakeValve(int pin, PinState activePinState) : RelayDevice(pin, activePinState) {
    Serial.println("Intake Valve : Intializing");
};

void IntakeValve::setup() {
    Serial.println("Intake Valve : Setup");
    RelayDevice::setup();
};

void IntakeValve::loop() {
    Serial.println("Intake Valve : Loop");
    RelayDevice::loop();
};

void IntakeValve::open() {
    Serial.println("Intake Valve : Open");
    RelayDevice::open();
};

void IntakeValve::close() {
    Serial.println("Intake Valve : Close");
    RelayDevice::close();
};
