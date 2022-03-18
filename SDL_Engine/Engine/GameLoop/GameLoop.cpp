#include "GameLoop.h"

GameLoop::GameLoop() {
    timer = new Timer();
}

GameLoop::~GameLoop() {
    delete timer;
    timer = nullptr;
}

void GameLoop::Run(Graphics* graphics, InputController* input, std::vector<GameObject*>& sceneObjects) {
    // Clear previous frame
    graphics->Clear();

    double currentTime = timer->GetCurrentTime();
    double frameTime = currentTime - previousTime;

    // Update previous time
    previousTime = currentTime;

    // Accumulate time difference
    timeLag += frameTime;

    // Input
    Input(input);

    // Physics Update
    int physicsUpdates = 0;

    while (timeLag >= FIXED_DELTA_TIME && physicsUpdates < MAX_PHYSICS_UPDATES) {
        physicsUpdates++;
        Update(sceneObjects);
        timeLag -= FIXED_DELTA_TIME;
        currentTime += FIXED_DELTA_TIME;
    }

    // Render all objects from current scene
    Render(graphics, sceneObjects);
}

void GameLoop::Input(const InputController* input) const {
    SDL_Event currentEvent;

    while (SDL_PollEvent(&currentEvent) != 0) {
        input->ProcessInput(currentEvent);
    }
}

void GameLoop::Update(std::vector<GameObject*>& sceneObjects) const {
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

void GameLoop::Render(Graphics* graphics, std::vector<GameObject*>& sceneObjects) const {
    for (int index = 0; index < sceneObjects.size(); index++) {
        sceneObjects[index]->Render(graphics);
    }

    graphics->Render();

    //graphics->Render(timeLag / FIXED_DELTA_TIME);
}