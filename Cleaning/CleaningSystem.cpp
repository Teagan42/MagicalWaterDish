#include "CleaningSystem.h"

CleaningSystem::CleaningSystem(IntakeValve *intakeValve, InjectionPump *injectionPump, CleaningCycle *cleaningCycle, Drain *drains, unsigned int drainCount)
{
    Serial.println("Cleaning System : Initializing");
    this->_intakeValve = intakeValve;
    this->_injectionPump = injectionPump;
    this->_cycles = cleaningCycle;
    this->_activeCycle = nullptr;
    this->_isActive = false;
    this->_drains = drains;
    this->_drainCount = drainCount;
};

void CleaningSystem::setup()
{
    Serial.println("Cleaning System : Setup");
    this->_intakeValve->setup();
    this->_injectionPump->setup();
    for (unsigned int i = 0; i < this->_drainCount; i++)
    {
        Drain drain = this->_drains[i];
        drain.setup();
    }
};

void CleaningSystem::loop()
{
    Serial.println("Cleaning System : Loop");
    if (!this->_isActive || this->_activeCycle == nullptr)
    {
        deactivate();
        return;
    }
    if (this->_cycleStartedAt > 0 && millis() - this->_cycleStartedAt >= this->_activeCycle->duration)
    {
        this->setActiveCycle(this->_activeCycle->next);
    }
};

void CleaningSystem::openDrains()
{
    for (unsigned int i = 0; i < this->_drainCount; i++)
    {
        Drain drain = this->_drains[i];
        drain.openDrain();
    }
};

void CleaningSystem::closeDrains()
{
    for (unsigned int i = 0; i < this->_drainCount; i++)
    {
        Drain drain = this->_drains[i];
        drain.closeDrain();
    }
};

void CleaningSystem::onCycleEnd(CleaningCycle *cycle)
{
    this->_cycleStartedAt = 0;
    switch (cycle->cycle)
    {
    case Cleaning::DRAIN:
        this->closeDrains();
        break;
    case Cleaning::WASH:
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    case Cleaning::RINSE:
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    case Cleaning::SOAK:
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    case Cleaning::DONE:
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        this->deactivate();
        break;
    default:
        break;
    }
};

void CleaningSystem::onCycleStart(CleaningCycle *cycle)
{
    this->_cycleStartedAt = millis();
    switch (cycle->cycle)
    {
    case Cleaning::DRAIN:
        this->openDrains();
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    case Cleaning::WASH:
        this->_injectionPump->turnOn();
        this->_intakeValve->open();
        break;
    case Cleaning::RINSE:
        this->_injectionPump->turnOff();
        this->_intakeValve->open();
        break;
    case Cleaning::SOAK:
        this->closeDrains();
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    case Cleaning::DONE:
        this->closeDrains();
        this->_injectionPump->turnOff();
        this->_intakeValve->close();
        break;
    default:
        break;
    }
};

void CleaningSystem::setActiveCycle(CleaningCycle *cycle)
{
    Serial.println("Cleaning System : Set Active Cycle");
    if (this->_activeCycle != nullptr)
    {
        this->onCycleEnd(this->_activeCycle);
    }
    this->_activeCycle = cycle;
    if (this->_activeCycle == nullptr)
    {
        this->deactivate();
        return;
    } else {
        this->onCycleStart(this->_activeCycle);
    }
};

void CleaningSystem::activate()
{
    Serial.println("Cleaning System : Activate");
    this->_isActive = true;
    this->setActiveCycle(this->_cycles);
};

void CleaningSystem::deactivate()
{
    Serial.println("Cleaning System : Deactivate");
    this->_cycleStartedAt = 0;
    this->_activeCycle = nullptr;
    this->_isActive = false;
};
