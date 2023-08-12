#include "Drain.h"

Drain::Drain(int pin) {
    Serial.println("Drain : Initializating");
    this->_pin = pin;
};

void Drain::setup() {
    Serial.println("Drain : Setup");
    pinMode(this->_pin, OUTPUT);
};

void Drain::loop() {
    Serial.println("Drain : Loop");
};

void Drain::closeDrain() {
    return;
};

void Drain::openDrain() {
    return;
};

DigitalDrain::DigitalDrain(int pin, PinState openPinState) : Drain(pin) {
    Serial.println("Digial Drain : Initializing");
    this->_openPinState = openPinState;
};

void DigitalDrain::closeDrain() {
    Serial.println("Digial Drain : Close Drain");
    digitalWrite(this->_pin, !this->_openPinState);
};

void DigitalDrain::openDrain() {
    Serial.println("Digital Drain: Open Drain");
    digitalWrite(this->_pin, this->_openPinState);
};

PWMDrain::PWMDrain(int pin, int openPin, int closePin) : Drain(pin) {
    Serial.println("PWM Drain : Initializing");
    this->_openPin = openPin;
    this->_closePin = closePin;
};

void PWMDrain::setup() {
    Serial.println("PWM Drain : Setup");
    pinMode(this->_closePin, OUTPUT);
    pinMode(this->_openPin, OUTPUT);
};

void PWMDrain::loop() {
    Serial.println("PWM Drain : Loop");
    if (this->_activeStart > 0 && millis() - this->_activeStart > 30000) {
        analogWrite(this->_pin, 0);
        digitalWrite(this->_closePin, LOW);
        digitalWrite(this->_openPin, LOW);
        this->_activeStart = 0;
        this->_inactiveStart = millis();
    } else if (this->_inactiveStart > 0 && millis() - this->_inactiveStart > 30000) {
        if (this->_state == CLOSED) {
            this->closeDrain();
        } else if (this->_state == OPEN) {
            this->openDrain();
        }
    }
}

void PWMDrain::openDrain() {
    Serial.println("PWM Drain : Open Drain");
    analogWrite(this->_pin, 255);
    digitalWrite(this->_closePin, LOW);
    digitalWrite(this->_openPin, HIGH);
    this->_inactiveStart = 0;
    this->_activeStart = millis();
};

void PWMDrain::closeDrain() {
    Serial.println("PWM Drain : Close Drain");
    analogWrite(this->_pin, 255);
    digitalWrite(this->_closePin, HIGH);
    digitalWrite(this->_openPin, LOW);
    this->_inactiveStart = 0;
    this->_activeStart = millis();
}