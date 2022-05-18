#include "DestructibleHealthComponent.h"
#include "../../../Engine/GameObject/GameObject.h"

void DestructibleHealthComponent::Init() {
    HealthComponent::Init();

    image = static_cast<ImageComponent*>(objectLinkedTo->GetComponent("Image"));
    grassTexture = TextureLocator::GetTextureManager()->GetTexture("Resources/Images/WorldScene/Sprite/Grass/grass.png");
}

void DestructibleHealthComponent::AdjustHealth(int healthAdjustment) {
    HealthComponent::AdjustHealth(healthAdjustment);

    // Destroy when out of health
    if (model->GetHealth() <= 0) {
        objectLinkedTo->SetComponentStatus("Physics", false);
        image->SetTexture(grassTexture);
    }
}
