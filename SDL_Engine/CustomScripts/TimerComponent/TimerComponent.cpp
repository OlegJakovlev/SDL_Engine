#include "TimerComponent.h"

TimerComponent::~TimerComponent() {
    delete model;
    model = nullptr;

    delete view;
    view = nullptr;

    delete levelTimer;
    levelTimer = nullptr;
}

void TimerComponent::Init() {
    AbstractComponent::Init();
    view->Init();

    levelTimer = new Timer();
    levelTimer->Reset();
}

void TimerComponent::LoadConfig(const nlohmann::json& config) {
    model = new TimerComponentModel();
    view = new TimerComponentView(model);

    model->AddTime(std::stod(config.at("initialTime").get<std::string>()));
    view->LoadConfig(config.at("view"));
}

void TimerComponent::Update() {
    levelTimer->Stop();
    
    model->SubstractTime(levelTimer->GetElapsedTime());
    view->UpdateScoreText();

    levelTimer->Reset();
}

void TimerComponent::Render() {
    view->Render();
}