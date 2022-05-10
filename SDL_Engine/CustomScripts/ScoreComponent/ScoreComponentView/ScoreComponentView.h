#pragma once

#ifndef ScoreComponentView_H
#define ScoreComponentView_H

#include "../../../Engine/Component/AbstractComponent.h"
#include "../ScoreComponentModel/ScoreComponentModel.h"
#include "../../../Engine/Component/TextComponent/TextComponent.h"

class ScoreComponentView : public AbstractComponent {
public:
    ScoreComponentView(const ScoreComponentModel* newModel);
    ~ScoreComponentView();

    void Init() override;
    void LoadConfig(const nlohmann::json& config) override;
    void Render() override;

    void UpdateScoreText();

private:
    const ScoreComponentModel* model;

    TextComponent* scoreText;
    GameObject::GameObject* fakeParent;
};

#endif