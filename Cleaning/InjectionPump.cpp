#include "InjectionPump.h"

InjectionPump::InjectionPump(int pin, PinState activePinState) : RelayDevice(pin, activePinState) {
    Serial.println("Injjection Pump : Intializing");
};

void InjectionPump::setup() {
    Serial.println("Injection Pump : Setup");
    RelayDevice::setup();
};

void InjectionPump::loop() {
    Serial.println("Injection Pump : Loop");
    RelayDevice::loop();
};

void InjectionPump::turnOff() {
    Serial.println("Injection Pump : Turn Off");
    RelayDevice::open();
};

void InjectionPump::turnOn() {
    Serial.println("Injection Pump : Turn On");
    RelayDevice::close();
};