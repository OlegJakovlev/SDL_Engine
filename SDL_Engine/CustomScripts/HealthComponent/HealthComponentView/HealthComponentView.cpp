#include "HealthComponentView.h"
#include "../../../Engine/Factories/GameObjectFactory/GameObjectFactory.h"

HealthComponentView::HealthComponentView(const HealthComponentModel* newModel) : model(newModel) {
    scoreText = new TextComponent();
}

HealthComponentView::~HealthComponentView() {
    delete scoreText;
    scoreText = nullptr;

    delete fakeParent;
    fakeParent = nullptr;
}

void HealthComponentView::Init() {
    scoreText->Init();
    UpdateHealthText();
}

void HealthComponentView::LoadConfig(const nlohmann::json& config) {
    scoreText->LoadConfig(config.at("textConfig"));

    // Create fake parent to have global position controls over the text
    fakeParent = GameObjectFactory::Instance()->CreateGameObject("FakeParent");
    fakeParent->SetGlobalPosition(config.value("position", Vector2::Vector2<int>(0,0)));

    scoreText->LinkWithObject(fakeParent);
}

void HealthComponentView::Render() {
    scoreText->Render();
}

void HealthComponentView::UpdateHealthText() {
    scoreText->SetText("Health: " + std::to_string(model->GetHealth()));
}
