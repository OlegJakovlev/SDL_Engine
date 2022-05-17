#pragma once

#ifndef ScoreMultiplier_H
#define ScoreMultiplier_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../PickableComponent/PickableComponent.h"
#include "../ScoreComponent/ScoreComponent.h"

class ScoreMultiplier : public AbstractComponent {
    void Init() override;

private:
    void CustomPickUp();

    PickableComponent* pickableComponent;
};

#endif