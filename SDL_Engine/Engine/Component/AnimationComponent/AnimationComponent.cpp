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

    if (!isPaused) {
        // If time passed, save the new time
        if (currentTime - previosFrameTime > frameSwitchTime) {
            previosFrameTime = currentTime;

            // Increment frame if not last
            if (currentFrame != animation.end()) {
                currentFrame = std::next(currentFrame);

                // Set new frame
                imageComponent->SetTexture(*currentFrame);
            }
            else {
                isFinished = true;
            }
        }
    }
}

void AnimationComponent::PlayAnimation(const std::string& animationName) {
    // Get texture before animation
    beforeAnimationTexture = imageComponent->GetTexture();
    
    // Get animation with first frame
    animation = AnimatorLocator::GetAnimator()->GetAnimation(animationName);
    currentFrame = animation.begin();

    // Reset flags
    isFinished = false;
    isPaused = false;

    // Start the timer
    previosFrameTime = timer.GetCurrentTime();
}

void AnimationComponent::PauseAnimation() {
    isPaused = true;
}
