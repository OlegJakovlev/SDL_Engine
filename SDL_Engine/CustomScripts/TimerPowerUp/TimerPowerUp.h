#pragma once

#ifndef TimerPowerUp_H
#define TimerPowerUp_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../TimerComponent/TimerComponent.h"
#include "../PickableComponent/PickableComponent.h"

class TimerPowerUp : public AbstractComponent {
    void Init() override;

private:
    TimerComponent* levelTimer;
    PickableComponent* pickableComponent;
};

#endif