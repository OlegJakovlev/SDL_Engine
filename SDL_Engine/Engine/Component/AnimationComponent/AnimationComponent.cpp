#include "AnimationComponent.h"
#include "../../GameManager.h"

AnimationComponent::~AnimationComponent() {
    imageComponent = nullptr;
    beforeAnimationTexture = nullptr;

    animationEndFrameEvents.clear();
}

void AnimationComponent::Init() {
    AbstractComponent::Init();

    imageComponent = static_cast<ImageComponent*>(objectLinkedTo->GetComponent("Image"));

    // Initialize timer
    timer = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()->GetTimer();
}

void AnimationComponent::Update() {
    double currentTime = timer.GetCurrentTime();

    if (isPaused || isFinished) return;
    if (animationData.animationFrames.size() <= 0) return;

    // If time passed, save the new time
    if (currentTime - previosFrameTime > animationData.frameDelays.at(currentFrameIndex)) {
        previosFrameTime = currentTime;

        // If reached end
        if (currentFrameIndex == animationData.animationFrames.size() - 1) {
            if (animationData.loop == AnimationData::AnimationType::ONE_OFF) {
                isFinished = true;
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
        }

        // Reset texture with frame on finish
        if (isFinished) {
            imageComponent->SetTexture(beforeAnimationTexture);
            imageComponent->SetTextureFrame(nullptr);
            beforeAnimationTexture = nullptr;

            // Call events
            for (auto& endFrameEvent : animationEndFrameEvents) {
                endFrameEvent();
            }
        }
        else {
            currentFrameIndex += step;

            imageComponent->SetTexture(animationData.fullTexture);
            imageComponent->SetTextureFrame(&animationData.animationFrames.at(currentFrameIndex));
        }
    }
}

void AnimationComponent::PlayAnimation(const std::string& animationName) {
    // Get texture before animation
    beforeAnimationTexture = imageComponent->GetTexture();
    
    // Get animation data
    animationData = AnimatorLocator::GetAnimator()->GetAnimation(animationName);

    // Clear events on new animation
    animationEndFrameEvents.clear();

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

void AnimationComponent::HaltAnimation() {
    isFinished = true;
}

void AnimationComponent::AddFrameEvent(std::function<void()> functionEvent) {
    animationEndFrameEvents.push_back(functionEvent);
}

int AnimationComponent::GetAnimationFramesAmount() {
    return animationData.animationFrames.size();
}
