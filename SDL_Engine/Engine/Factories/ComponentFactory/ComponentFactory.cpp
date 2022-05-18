#include "ComponentFactory.h"

ComponentFactory* ComponentFactory::sInstance = nullptr;

ComponentFactory::~ComponentFactory() {
    delete sInstance;
    sInstance = nullptr;
}

ComponentFactory* ComponentFactory::Instance() {
    if (sInstance == nullptr) sInstance = new ComponentFactory();
    return sInstance;
}

AbstractComponent* ComponentFactory::CreateComponent(const std::string& componentName) {
    // Base components
    if (componentName == "Text") {
        return new TextComponent();
    }
    
    if (componentName == "Image") {
        return new ImageComponent();
    }

    if (componentName == "Animation") {
        return new AnimationComponent();
    }

    if (componentName == "Physics") {
        return new PhysicsComponent();
    }

    if (componentName == "ObjectPool") {
        return new ObjectPoolComponent();
    }

    // Composite components
    if (componentName == "GameLoopView") {
        return new GameLoopView();
    }

    if (componentName == "PlayerMovement") {
        return new PlayerMovement();
    }

    if (componentName == "PlayerScore") {
        return new ScoreComponent();
    }

    if (componentName == "PlayerHealth") {
        return new PlayerHealthComponent();
    }

    if (componentName == "DestructibleHealth") {
        return new DestructibleHealthComponent();
    }

    if (componentName == "BombSpawner") {
        return new BombSpawnerComponent();
    }

    if (componentName == "LevelTimer") {
        return new TimerComponent();
    }

    if (componentName == "Pickable") {
        return new PickableComponent();
    }

    if (componentName == "TimerPowerUp") {
        return new TimerPowerUp();
    }

    if (componentName == "CoinPickUp") {
        return new CoinPickUp();
    }

    if (componentName == "MenuView") {
        return new MenuView();
    }

    if (componentName == "WinnerView") {
        return new WinnerView();
    }

    if (componentName == "FlyingBird") {
        return new FlyingBird();
    }

    if (componentName == "Bomb") {
        return new BombComponent();
    }

    if (componentName == "Explosion") {
        return new ExplosionComponent();
    }

    if (componentName == "Damageable") {
        return new DamageableComponent();
    }

    if (componentName == "ScoreMultiplier") {
        return new ScoreMultiplier();
    }

    return nullptr;
}