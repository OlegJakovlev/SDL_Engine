#include "PlayerMovement.h"
#include "../../Engine/GameManager.h"

void PlayerMovement::Init() {
	physicsComponent = static_cast<PhysicsComponent*>(objectLinkedTo->GetComponent("Physics"));
	animationComponent = static_cast<AnimationComponent*>(objectLinkedTo->GetComponent("Animation"));

	// Get input controller and link actions of movement
	InputController* inputController = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetInputConfigurator()->GetInputController();

	if (controllerAgentName == "Player1") {
		inputController->LinkAction("player1MoveLeft", std::bind(&PlayerMovement::MoveLeft, this));
		inputController->LinkAction("player1MoveRight", std::bind(&PlayerMovement::MoveRight, this));
		inputController->LinkAction("player1MoveUp", std::bind(&PlayerMovement::MoveUp, this));
		inputController->LinkAction("player1MoveDown", std::bind(&PlayerMovement::MoveDown, this));
	}

	else if (controllerAgentName == "Player2") {
		inputController->LinkAction("player2MoveLeft", std::bind(&PlayerMovement::MoveLeft, this));
		inputController->LinkAction("player2MoveRight", std::bind(&PlayerMovement::MoveRight, this));
		inputController->LinkAction("player2MoveUp", std::bind(&PlayerMovement::MoveUp, this));
		inputController->LinkAction("player2MoveDown", std::bind(&PlayerMovement::MoveDown, this));
	}
}

void PlayerMovement::Update() {
	if (!animationComponent->IsPlaying()) {
		animationComponent->PlayAnimation((controllerAgentName == "Player1") ? "player1Idle" : "player2Idle");
	}
}

void PlayerMovement::LoadConfig(const nlohmann::json& config) {
	controllerAgentName = config.at("playerName");
}

void PlayerMovement::MoveLeft() {
	movementDirection = Vector2::Vector2<int>(-1, 0) * 32;
	physicsComponent->SetVelocity(movementDirection);
	animationComponent->PlayAnimation((controllerAgentName == "Player1") ? "player1GoLeft" : "player2GoLeft");
}

void PlayerMovement::MoveRight() {
	movementDirection = Vector2::Vector2<int>(1, 0) * 32;
	physicsComponent->SetVelocity(movementDirection);
	animationComponent->PlayAnimation((controllerAgentName == "Player1") ? "player1GoRight" : "player2GoRight");
}

void PlayerMovement::MoveUp() {
	movementDirection = Vector2::Vector2<int>(0, -1) * 32;
	physicsComponent->SetVelocity(movementDirection);
	animationComponent->PlayAnimation((controllerAgentName == "Player1") ? "player1GoUp" : "player2GoUp");
}

void PlayerMovement::MoveDown() {
	movementDirection = Vector2::Vector2<int>(0, 1) * 32;
	physicsComponent->SetVelocity(movementDirection);
	animationComponent->PlayAnimation((controllerAgentName == "Player1") ? "player1GoDown" : "player2GoDown");
}
