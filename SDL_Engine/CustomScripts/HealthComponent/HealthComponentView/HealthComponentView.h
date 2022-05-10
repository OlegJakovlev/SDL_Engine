#pragma once

#ifndef HealthComponentView_H
#define HealthComponentView_H

#include "../../../Engine/Component/AbstractComponent.h"
#include "../HealthComponentModel/HealthComponentModel.h"
#include "../../../Engine/Component/TextComponent/TextComponent.h"

class HealthComponentView : public AbstractComponent {
public:
    HealthComponentView(const HealthComponentModel& newModel);
    ~HealthComponentView();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

    void UpdateHealthText();

private:
    const HealthComponentModel model;

    TextComponent* scoreText;
    GameObject::GameObject* fakeParent;
};

#endif