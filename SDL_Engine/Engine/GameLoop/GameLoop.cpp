#include "GameLoop.h"
#include "../SceneManagment/Scene.h"

GameLoop::GameLoop() {
    timer = new Timer();
}

void GameLoop::Initialize(Scene* masterScene) {
    GameObject::GameObject* gameLoopStats = masterScene->GetSceneObjectByName("GameLoopStats");
    if (gameLoopStats == nullptr) return;

    gameStatsView = static_cast<GameLoopView*>(gameLoopStats->GetComponent("GameLoopView"));
}

GameLoop::~GameLoop() {
    delete timer;
    timer = nullptr;
}

void GameLoop::Run(InputController* input, std::vector<GameObject::GameObject*>& sceneObjects) {
    double currentTime = timer->GetCurrentTime();
    double frameTime = currentTime - previousTime;

    if (frameTime > 1) frameTime = 1;
    
    int physicsUpdates = 0;

    // Update previous time
    previousTime = currentTime;

    // Accumulate time difference
    timeLag += frameTime;

    // Input
    if (inputActive) {
        Input(input);
        
        // Measure input performance
        inputTime = timer->GetCurrentTime() - previousTime;
        if (gameStatsView != nullptr) gameStatsView->SetInputPerformaceText(std::to_string(inputTime * 1000));
    }

    // Physics Update
    if (updateActive) {
        while (timeLag >= SECONDS_PER_UPDATE && physicsUpdates < MAX_PHYSICS_UPDATES) {
            physicsUpdates++;
            Update(sceneObjects);
            timeLag -= SECONDS_PER_UPDATE;
            currentTime += SECONDS_PER_UPDATE;
        }

        // Measure update performance
        updateTime = timer->GetCurrentTime() - inputTime - previousTime;
        if (gameStatsView != nullptr) gameStatsView->SetUpdatePerformaceText(std::to_string(updateTime * 1000));
    }

    // Render
    if (renderActive) {
        Graphics::Instance()->RenderClear();
        Graphics::Instance()->Render(sceneObjects, timeLag / SECONDS_PER_UPDATE);

        // Measure render performance
        renderTime = timer->GetCurrentTime() - updateTime - previousTime;
        if (gameStatsView != nullptr) gameStatsView->SetRenderPerformaceText(std::to_string(renderTime * 1000));

        Graphics::Instance()->RenderPresent();
    }

    SDL_Delay(10);
}

const Timer& GameLoop::GetTimer() {
    return *timer;
}

void GameLoop::ToggleInput() {
    inputActive = !inputActive;

    std::string textStatus = (inputActive) ? "ON" : "OFF";
    Logger::Instance().LogWarning("GameLoop Input Component: " + textStatus);

    if (!inputActive && gameStatsView != nullptr) gameStatsView->SetInputPerformaceText("Disabled");
}

void GameLoop::ToggleUpdate() {
    updateActive = !updateActive;

    std::string textStatus = (updateActive) ? "ON" : "OFF";
    Logger::Instance().LogWarning("GameLoop Update Component: " + textStatus);

    if (!updateActive && gameStatsView != nullptr) gameStatsView->SetUpdatePerformaceText("Disabled");
}

void GameLoop::ToggleRender() {
    renderActive = !renderActive;

    std::string textStatus = (renderActive) ? "ON" : "OFF";
    Logger::Instance().LogWarning("GameLoop Render Component: " + textStatus);

    if (!renderActive && gameStatsView != nullptr) gameStatsView->SetRenderPerformaceText("Disabled");
}

void GameLoop::DeleteMarkedObjects(std::vector<GameObject::GameObject*>& sceneObjects) {
    if (sceneObjects.empty()) return;

    // Delete game objects with allocated data
    for (auto& gameObject : sceneObjects) {
        if (gameObject->ShouldBeDeleted()) {
            delete gameObject;
            gameObject = nullptr;
        }
        else {
            std::vector<GameObject::GameObject*> tmp = gameObject->GetChildObjects();
            DeleteMarkedObjects(tmp);
        }
    }
}

void GameLoop::Input(InputController* input) {
    SDL_Event currentEvent;

    while (SDL_PollEvent(&currentEvent) != 0) {
        input->ProcessInput(currentEvent);
    }

    input->ProcessActiveEvents();
}

void GameLoop::Update(std::vector<GameObject::GameObject*>& sceneObjects) {
    // Components update
    for (int index = 0; index < sceneObjects.size(); index++) {
        sceneObjects[index]->Update();
    }
}