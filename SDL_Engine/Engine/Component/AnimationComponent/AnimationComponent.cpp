#include "AnimationComponent.h"
#include "../../GameManager.h"  

AnimationComponent::~AnimationComponent() {
    imageComponent = nullptr;
    beforeAnimationTexture = nullptr;
}

void AnimationComponent::Init() {
    AbstractComponent::Init();

    imageComponent = static_cast<ImageComponent*>(objectLinkedTo->GetComponent("Image"));

    // Initialize timer
    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
}

void AnimationComponent::Update() {
    double currentTime = timer.GetCurrentTime();

    if (isFinished && beforeAnimationTexture != nullptr) {
        imageComponent->SetTexture(beforeAnimationTexture);
        beforeAnimationTexture = nullptr;
        return;
    }

    if (isPaused) return;

    // If time passed, save the new time
    if (currentTime - previosFrameTime > animationData.frameDelays.at(currentFrameIndex)) {
        previosFrameTime = currentTime;

        // If reached end
        if (currentFrameIndex == animationData.animation.size() - 1) {
            if (animationData.loop == AnimationData::AnimationType::ONE_OFF) {
                isFinished = true;
                return;
            }
            // Swap direction
            else if (animationData.loop == AnimationData::AnimationType::PING_PONG) {
                step *= -1;
            }
            // Reset to start position
            else if (animationData.loop == AnimationData::AnimationType::LOOP) {
                currentFrameIndex = -1;
            }
        }

        if (animationData.loop == AnimationData::AnimationType::PING_PONG && currentFrameIndex == 0 && step == -1) {
            isFinished = true;
            return;
        }

        currentFrameIndex += step;

        imageComponent->SetTexture(animationData.animation.at(currentFrameIndex));
    }
}

void AnimationComponent::PlayAnimation(const std::string& animationName) {
    // Get texture before animation
    beforeAnimationTexture = imageComponent->GetTexture();
    
    // Get animation data
    animationData = AnimatorLocator::GetAnimator()->GetAnimation(animationName);

    // Reset flags
    isFinished = false;
    isPaused = false;
    currentFrameIndex = 0;
    step = 1;

    // Start the timer
    previosFrameTime = timer.GetCurrentTime();
}

void AnimationComponent::PauseAnimation() {
    isPaused = true;
}
