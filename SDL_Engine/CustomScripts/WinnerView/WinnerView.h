#pragma once

#ifndef WinnerView_H
#define WinnerView_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/TextComponent/TextComponent.h"
#include "../../Engine/GameData/GameData.h"

class WinnerView : public AbstractComponent {
public:
    void Init() override;

private:
    TextComponent* winnerText;
};

#endif