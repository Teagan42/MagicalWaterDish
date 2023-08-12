#ifndef LIB_INJECTION_PUMP_H
#define LIB_INJECTION_PUMP_H

#include <Arduino.h>
#include "../Common/Relay.h"

class InjectionPump : protected RelayDevice {
public:
    InjectionPump(int pin, PinState activePinState);
    void setup();
    void loop();
    void turnOn();
    void turnOff();
};

#endif