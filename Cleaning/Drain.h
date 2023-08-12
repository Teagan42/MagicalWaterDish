#ifndef LIB_DRAIN_H
#define LIB_DRAIN_H

#include <Arduino.h>

enum DrainState {
    OPEN,
    CLOSED
};

class Drain {
protected:
    int _pin;
public:
    Drain(int pin);
    virtual void setup();
    virtual void loop();
    virtual void openDrain();
    virtual void closeDrain();
};

class DigitalDrain : public Drain {
private:
    PinState _openPinState;
public:
    DigitalDrain(int pin, PinState openPinState);
    void openDrain() override;
    void closeDrain() override;
};

class PWMDrain : public Drain {
private:
    int _openPin;
    int _closePin;
    DrainState _state = CLOSED;
    long _activeStart;
    long _inactiveStart;
public:
    PWMDrain(int pin, int openPin, int closePin);
    void setup() override;
    void loop() override;
    void openDrain() override;
    void closeDrain() override;
};

#endif