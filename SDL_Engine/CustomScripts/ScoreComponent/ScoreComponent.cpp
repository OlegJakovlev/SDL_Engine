#include "ScoreComponent.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/GameObject/GameObject.h"

ScoreComponent::~ScoreComponent() {
    delete model;
    delete view;
}

void ScoreComponent::Init() {
    AbstractComponent::Init();
    view->Init();

    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();

    GameData::Instance()->AddDataEntry(objectLinkedTo->GetName(), std::to_string(model->GetScore()));
}

void ScoreComponent::LoadConfig(const nlohmann::json& config) {
    model = new ScoreComponentModel();
    view = new ScoreComponentView(model);

    view->LoadConfig(config.at("view"));
}

void ScoreComponent::Update() {
    if (!multiplierStatus) return;

    if (timer.GetCurrentTime() > multiplierTimer + multiplierDuration) TurnOffMultiplier();
}

void ScoreComponent::Render() {
    view->Render();
}

void ScoreComponent::AdjustScore(int scoreAdjustment) {
    if (multiplierStatus) scoreAdjustment *= 2;

    // Update model
    if (scoreAdjustment < 0) {
        model->SubstractScore(scoreAdjustment * -1);
    }
    else {
        model->AddScore(scoreAdjustment);
    }

    // Update game data
    GameData::Instance()->ReplaceDataEntry(objectLinkedTo->GetName(), std::to_string(model->GetScore()));

    // Log update
    Logger::Instance().LogMessage(objectLinkedTo->GetName() + " new score is : " + std::to_string(model->GetScore()));

    // Update view
    view->UpdateScoreText();
}

void ScoreComponent::TurnOnMultiplier(double duration) {
    multiplierDuration = duration;
    multiplierStatus = true;
    multiplierTimer = timer.GetCurrentTime();
}

void ScoreComponent::TurnOffMultiplier() {
    multiplierStatus = false;
    multiplierDuration = 0;
}
