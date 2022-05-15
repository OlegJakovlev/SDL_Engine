#include "ScoreComponent.h"
#include "../../Engine/GameObject/GameObject.h"

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

    // Update game data
    std::string playerName = objectLinkedTo->GetName();
    std::unordered_map<std::string, std::string>::iterator it = GameData::Instance()->data.find(playerName);

    if (GameData::Instance()->data.empty() || it == GameData::Instance()->data.end()) {
        GameData::Instance()->data.emplace(std::make_pair(playerName, std::to_string(model->GetScore())));
    }
    else {
        GameData::Instance()->data[playerName] = std::to_string(model->GetScore());
    }

    Logger::Instance().LogMessage(objectLinkedTo->GetName() + " new score is : " + std::to_string(model->GetScore()));

    // Update view
    view->UpdateScoreText();
}