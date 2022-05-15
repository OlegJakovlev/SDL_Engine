#pragma once

#ifndef CoinPickUp_H
#define CoinPickUp_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../PickableComponent/PickableComponent.h"
#include "../ScoreComponent/ScoreComponent.h"

class CoinPickUp : public AbstractComponent {
    void Init() override;

private:
    void CustomPickUp();

    PickableComponent* pickableComponent;
};

#endif