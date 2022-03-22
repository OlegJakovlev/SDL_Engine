#include "GameLoop.h"

GameLoop::GameLoop() {
    timer = new Timer();
}

GameLoop::~GameLoop() {
    delete timer;
    timer = nullptr;
}

void GameLoop::Run(Graphics* graphics, InputController* input, std::vector<GameObject::GameObject*>& sceneObjects) {
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

    // Physics Update
    while (timeLag >= SECONDS_PER_UPDATE && physicsUpdates < MAX_PHYSICS_UPDATES) {
        physicsUpdates++;
        Update(sceneObjects);
#if _DEBUG
        printf("Update %d\n", physicsUpdates);
#endif
        timeLag -= SECONDS_PER_UPDATE;
        currentTime += SECONDS_PER_UPDATE;
    }

    // Render
    Render(graphics, timeLag / SECONDS_PER_UPDATE);
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
        if ((*it)->ShouldBeDeleted()) (*it)->Destroy();

        // Pointers should be updated after deleting an object
        it = sceneObjects.erase(it);
    }
}

void GameLoop::Render(Graphics* graphics, double normalizedStepBetweenUpdates) const {
    graphics->Render(normalizedStepBetweenUpdates);
    printf("1\n");
    //graphics->Render(timeLag / SECONDS_PER_UPDATE);
}