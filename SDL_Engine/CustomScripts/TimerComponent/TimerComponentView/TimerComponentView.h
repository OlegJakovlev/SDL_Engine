#pragma once

#ifndef TimerComponentView_H
#define TimerComponentView_H

#include "../../../Engine/Component/AbstractComponent.h"
#include "../TimerComponentModel/TimerComponentModel.h"
#include "../../../Engine/Component/TextComponent/TextComponent.h"

class TimerComponentView : public AbstractComponent {
public:
    TimerComponentView(const TimerComponentModel* newModel);
    ~TimerComponentView();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

    void UpdateScoreText();

private:
    const TimerComponentModel* model;

    TextComponent* scoreText;
    GameObject::GameObject* fakeParent;
};

#endif