#ifndef LIB_INTAKE_VALVE
#define LIB_INTAKE_VALVE

#include <Arduino.h>
#include "Relay.h"

class IntakeValve : public RelayDevice {
public:
    IntakeValve(int pin, PinState activePinState);
    void setup();
    void loop();
    void open();
    void close();
};

#endif