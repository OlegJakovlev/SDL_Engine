#include "TimerComponent.h"
#include "../../Engine/GameManager.h"

TimerComponent::~TimerComponent() {
    delete model;
    model = nullptr;

    delete view;
    view = nullptr;
}

void TimerComponent::Init() {
    AbstractComponent::Init();
    view->Init();

    model->AddTime(initialTime);

    levelTimer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
    levelTimer.Reset();
}

void TimerComponent::LoadConfig(const nlohmann::json& config) {
    model = new TimerComponentModel();
    view = new TimerComponentView(model);

    initialTime = std::stod(config.at("initialTime").get<std::string>());

    view->LoadConfig(config.at("view"));
}

void TimerComponent::Update() {
    if (model->GetTimeLeft() <= 0) GameManager::Instance()->GetSceneManager()->LoadNextScene();

    levelTimer.Stop();
    
    model->SubstractTime(levelTimer.GetElapsedTime());
    view->UpdateScoreText();

    levelTimer.Reset();
}

void TimerComponent::Render() {
    view->Render();
}

void TimerComponent::AddGamePlayTime(int amountOfTime) {
    if (amountOfTime <= 0) return;
    model->AddTime(amountOfTime);
}