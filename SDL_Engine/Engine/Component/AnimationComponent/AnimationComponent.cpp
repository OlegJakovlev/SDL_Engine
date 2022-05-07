#include "AnimationComponent.h"
#include "../../GameManager.h"  

AnimationComponent::~AnimationComponent() {
    imageComponent = nullptr;
}

void AnimationComponent::Init() {
    AbstractComponent::Init();

    imageComponent = static_cast<ImageComponent*>(objectLinkedTo->GetComponent("Image"));

    // Initialize timer
    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
}

void AnimationComponent::LoadConfig(const nlohmann::json& config) {
}

void AnimationComponent::Update() {
    auto previousFrame = currentFrame;
    double currentTime = timer.GetCurrentTime();

    if (isPlaying) {
        // If time passed, save the new time and increment the frame
        if (currentTime - previosFrameTime > frameSwitchTime) {
            previosFrameTime = currentTime;
            std::next(currentFrame);
        }
    }

    if (previousFrame != currentFrame) imageComponent->SetTexture(*currentFrame);
}

void AnimationComponent::PlayAnimation(const std::string& animationName) {
    currentFrame = AnimatorLocator::GetAnimator()->GetAnimation(animationName).begin();
    previosFrameTime = timer.GetCurrentTime();
}

void AnimationComponent::PauseAnimation() {
    isPlaying = false;
}
