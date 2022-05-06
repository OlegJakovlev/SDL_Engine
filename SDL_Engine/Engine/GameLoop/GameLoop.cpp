#include "GameLoop.h"
#include "../SceneManagment/Scene.h"

GameLoop::GameLoop() {
    timer = new Timer();
}

void GameLoop::Initialize(Scene* masterScene) {
    GameObject::GameObject* gameLoopStats = masterScene->GetSceneObjectByName("GameLoopStats");
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
        gameStatsView->SetInputPerformaceText(std::to_string(inputTime));
    }
    else {
        gameStatsView->SetInputPerformaceText("Disabled");
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
        gameStatsView->SetUpdatePerformaceText(std::to_string(updateTime));
    }
    else {
        gameStatsView->SetUpdatePerformaceText("Disabled");
    }

    // Render
    if (renderActive) {
        Graphics::Instance()->RenderClear();
        Graphics::Instance()->Render(sceneObjects, timeLag / SECONDS_PER_UPDATE);

        // Measure render performance
        renderTime = timer->GetCurrentTime() - updateTime - previousTime;
        gameStatsView->SetRenderPerformaceText(std::to_string(renderTime));

        Graphics::Instance()->RenderPresent();
    }
    else {
        gameStatsView->SetRenderPerformaceText("Disabled");
    }
}

void GameLoop::ToggleInput() {
    inputActive = !inputActive;
}

void GameLoop::ToggleUpdate() {
    updateActive = !updateActive;
}

void GameLoop::ToggleRender() {
    renderActive = !renderActive;
}

void GameLoop::Input(InputController* input) {
    SDL_Event currentEvent;

    while (SDL_PollEvent(&currentEvent) != 0) {
        input->ProcessInput(currentEvent);
    }
}

void GameLoop::Update(std::vector<GameObject::GameObject*>& sceneObjects) {
    // Components update
    for (int index = 0; index < sceneObjects.size(); index++) {
        sceneObjects[index]->Update();
    }

    // Check if object should be deleted
    for (auto it = sceneObjects.begin(); it != sceneObjects.end(); it++) {
        if ((*it)->ShouldBeDeleted()) {
            (*it)->Destroy();

            // Pointers should be updated after deleting an object
            it = sceneObjects.erase(it);
        }
    }
}