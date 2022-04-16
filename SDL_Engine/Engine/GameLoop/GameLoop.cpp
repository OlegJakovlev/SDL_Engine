#include "GameLoop.h"

GameLoop::GameLoop() {
    timer = new Timer();
    statsView = GameObjectFactory::Instance()->CreateGameObjectFromFile(statsViewConfigPath);
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
    Input(input);

    // Measure input performance
    double inputTime = timer->GetCurrentTime() - previousTime;

    // Physics Update
    while (timeLag >= SECONDS_PER_UPDATE && physicsUpdates < MAX_PHYSICS_UPDATES) {
        physicsUpdates++;
        Update(sceneObjects);

        timeLag -= SECONDS_PER_UPDATE;
        currentTime += SECONDS_PER_UPDATE;
    }

    // Measure update performance
    double updateTime = timer->GetCurrentTime() - inputTime - previousTime;

    // Render
    Graphics::Instance()->RenderClear();
    Graphics::Instance()->Render(sceneObjects, timeLag / SECONDS_PER_UPDATE);

    // Measure render performance
    double renderTime = timer->GetCurrentTime() - updateTime - previousTime;

    //Graphics::Instance()->Render(view);
    Graphics::Instance()->RenderPresent();
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