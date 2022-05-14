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

void PlayerMovement::LoadConfig(const nlohmann::json& config) {
	controllerAgentName = config.at("playerName");
}

void PlayerMovement::MoveLeft() {
	physicsComponent->SetVelocity(Vector2::Vector2(-1, 0));
}

void PlayerMovement::MoveRight() {
	physicsComponent->SetVelocity(Vector2::Vector2(1, 0));
}

void PlayerMovement::MoveUp() {
	physicsComponent->SetVelocity(Vector2::Vector2(0, -1));
}

void PlayerMovement::MoveDown() {
	physicsComponent->SetVelocity(Vector2::Vector2(0, 1));
}
