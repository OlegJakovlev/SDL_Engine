#include "GameLoop.h"
#include "../SceneManagment/Scene.h"

GameLoop::GameLoop(Scene* linkTo) {
    timer = new Timer();
    linkedTo = linkTo;
}

void GameLoop::Initialize() {
    GameObject::GameObject* tmp = linkedTo->GetSceneObjectByName("GameLoopStats");
    gameStatsView = static_cast<GameLoopView*>(tmp->GetComponent("GameLoopView"));
}

GameLoop::~GameLoop() {
    delete timer;
    timer = nullptr;
    linkedTo = nullptr;
}

void GameLoop::Run(InputController* input, std::vector<GameObject::GameObject*>& sceneObjects) {
    if (gameStatsView == nullptr) Initialize();

    double currentTime = timer->GetCurrentTime();
    double frameTime = currentTime - previousTime;

    if (frameTime > 1) frameTime = 1;
    
    int physicsUpdates = 0;

    // Update previous time
    previousTime = currentTime;

    // Accumulate time difference
    timeLag += frameTime;

    // Input
    Input(input);

    // Measure input performance
    inputTime = timer->GetCurrentTime() - previousTime;
    gameStatsView->SetUpdatePerformaceText(std::to_string(inputTime));

    // Physics Update
    while (timeLag >= SECONDS_PER_UPDATE && physicsUpdates < MAX_PHYSICS_UPDATES) {
        physicsUpdates++;
        Update(sceneObjects);

        timeLag -= SECONDS_PER_UPDATE;
        currentTime += SECONDS_PER_UPDATE;
    }

    // Measure update performance
    updateTime = timer->GetCurrentTime() - inputTime - previousTime;
    gameStatsView->SetUpdatePerformaceText(std::to_string(updateTime));

    // Render
    Graphics::Instance()->RenderClear();
    Graphics::Instance()->Render(sceneObjects, timeLag / SECONDS_PER_UPDATE);

    // Measure render performance
    renderTime = timer->GetCurrentTime() - updateTime - previousTime;
    gameStatsView->SetUpdatePerformaceText(std::to_string(renderTime));

    Graphics::Instance()->RenderPresent();

    //gameStatsView
}

void GameLoop::Input(const InputController* input) const {
    SDL_Event currentEvent;

    while (SDL_PollEvent(&currentEvent) != 0) {
        input->ProcessInput(currentEvent);
    }
}

void GameLoop::Update(std::vector<GameObject::GameObject*>& sceneObjects) const {
    // Component and physics update
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