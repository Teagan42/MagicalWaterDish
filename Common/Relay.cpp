#include <Arduino.h>
#include "Relay.h"

RelayDevice::RelayDevice(int pin, PinState closedPinState) {
    Serial.println("Relay Device : Initializing");
    this->_pin = pin;
    this->_closedPinState = closedPinState;
    this->_state = Relay::OPEN;
};

void RelayDevice::setup() {
    Serial.println("Relay Device : Setup");
    pinMode(this->_pin, OUTPUT);
    this->_state = digitalRead(this->_pin) == this->_closedPinState ? Relay::CLOSED : Relay::OPEN;
};

void RelayDevice::loop() {
    Serial.println("Relay Device : Loop");
};

void RelayDevice::close() {
    Serial.println("Relay Device : Close");
    digitalWrite(this->_pin, this->_closedPinState);
    this->_state = Relay::CLOSED;
};

void RelayDevice::open() {
    Serial.println("Relay Device : Open");
    digitalWrite(this->_pin, !this->_closedPinState);
    this->_state = Relay::OPEN;
};