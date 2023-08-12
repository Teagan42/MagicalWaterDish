#ifndef LIB_CLEANING_SYSTEM_H
#define LIB_CLEANING_SYSTEM_H

#include "../Common/IntakeValve.h"
#include "InjectionPump.h"
#include "Drain.h"

struct Cleaning {
    enum Cycle {
        WASH,
        SOAK,
        DRAIN,
        RINSE,
        DONE
    };
};

struct CleaningCycle {
    Cleaning::Cycle cycle;
    unsigned long duration;
    CleaningCycle* next = nullptr;
};

class CleaningSystem {
private:
    IntakeValve* _intakeValve;
    InjectionPump* _injectionPump;
    CleaningCycle* _cycles;
    CleaningCycle* _activeCycle;
    Drain* _drains;
    unsigned int _drainCount;
    unsigned long _cycleStartedAt;
    bool _isActive;
    void openDrains();
    void closeDrains();
    void setActiveCycle(CleaningCycle* cycle);
    void onCycleStart(CleaningCycle* cycle);
    void onCycleEnd(CleaningCycle* cycle);
public:
    CleaningSystem(IntakeValve* intakeValve, InjectionPump* injectionPump, CleaningCycle* cycles, Drain* drains, unsigned int drainCount);
    void setup();
    void loop();
    void activate();
    void deactivate();
};

#endif