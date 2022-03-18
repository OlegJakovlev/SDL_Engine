#pragma once

#ifndef SceneManager_H
#define SceneManager_H

#include <vector>
#include "Scene.h"
#include "../ObserverPattern/Subject/ISubject.h"

class SceneManager : public ISubject {
public:
    SceneManager();
    ~SceneManager();

    Scene* GetCurrentScene();

    // Observer pattern for scene change event
    void Subscribe(IObserver* newSubscriber) override;
    void Unsubscribe(IObserver* subscriber) override;
    void Notify() override;

private:
    Scene* currentScene;
    std::vector<Scene*> scenesToBuild;

    // On scene change event
    std::vector<IObserver*> subscribers;
};

#endif
