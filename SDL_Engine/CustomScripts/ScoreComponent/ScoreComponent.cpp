#include "ScoreComponent.h"

ScoreComponent::~ScoreComponent() {
    delete model;
    delete view;
}

void ScoreComponent::Init() {
    AbstractComponent::Init();
    view->Init();
}

void ScoreComponent::LoadConfig(const nlohmann::json& config) {
    model = new ScoreComponentModel();
    view = new ScoreComponentView(model);

    view->LoadConfig(config.at("view"));
}

void ScoreComponent::Render() {
    view->Render();
}

void ScoreComponent::AdjustScore(int scoreAdjustment) {
    // Update model
    if (scoreAdjustment < 0) {
        model->SubstractScore(scoreAdjustment * -1);
    }
    else {
        model->AddScore(scoreAdjustment);
    }

    // Update view
    view->UpdateScoreText();
}