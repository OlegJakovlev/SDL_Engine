#include "TimerComponentView.h"
#include "../../../Engine/Factories/GameObjectFactory/GameObjectFactory.h"

TimerComponentView::TimerComponentView(const TimerComponentModel* newModel) : model(newModel) {
    scoreText = new TextComponent();
}

TimerComponentView::~TimerComponentView() {
    delete scoreText;
    scoreText = nullptr;

    delete fakeParent;
    fakeParent = nullptr;
}

void TimerComponentView::Init() {
    scoreText->Init();
    UpdateScoreText();
}

void TimerComponentView::LoadConfig(const nlohmann::json& config) {
    scoreText->LoadConfig(config.at("textConfig"));

    // Create fake parent to have global position controls over the text
    fakeParent = GameObjectFactory::Instance()->CreateGameObject("FakeParent");
    fakeParent->SetGlobalPosition(config.at("position").get<Vector2::Vector2<int>>());

    scoreText->LinkWithObject(fakeParent);
}

void TimerComponentView::Render() {
    scoreText->Render();
}

void TimerComponentView::UpdateScoreText() {
    scoreText->SetText(std::to_string((int) model->GetTimeLeft()));
}
