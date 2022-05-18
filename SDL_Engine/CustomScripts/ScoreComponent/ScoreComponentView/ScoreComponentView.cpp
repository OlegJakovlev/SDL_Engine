#include "ScoreComponentView.h"
#include "../../../Engine/Factories/GameObjectFactory/GameObjectFactory.h"

ScoreComponentView::ScoreComponentView(const ScoreComponentModel* newModel) : model(newModel) {
    scoreText = new TextComponent();
}

ScoreComponentView::~ScoreComponentView() {
    delete scoreText;
    scoreText = nullptr;

    delete fakeParent;
    fakeParent = nullptr;
}

void ScoreComponentView::Init() {
    scoreText->Init();
    UpdateScoreText();
}

void ScoreComponentView::LoadConfig(const nlohmann::json& config) {
    scoreText->LoadConfig(config.at("textConfig"));

    // Create fake parent to have global position controls over the text
    fakeParent = GameObjectFactory::Instance()->CreateGameObject("FakeParent");
    fakeParent->SetGlobalPosition(config.at("position").get<Vector2::Vector2<int>>());

    scoreText->LinkWithObject(fakeParent);
}

void ScoreComponentView::Render() {
    scoreText->Render();
}

void ScoreComponentView::UpdateScoreText() {
    scoreText->SetText("Score: " + std::to_string(model->GetScore()));
}
