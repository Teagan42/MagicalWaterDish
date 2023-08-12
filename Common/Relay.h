#ifndef LIB_RELAY_H
#define LIB_RELAY_H

#include <Arduino.h>

struct Relay {
    enum State {
        OPEN,
        CLOSED
    };
};

class RelayDevice {
private:
    int _pin;
    PinState _closedPinState;
    Relay::State _state;
public:
    RelayDevice(int pin, PinState closedPinState);
    void setup();
    void loop();
    void close();
    void open();
};

#endif