#include "PlayerMovement.h"
#include "../../Engine/GameManager.h"

void PlayerMovement::LoadConfig(const nlohmann::json& config) {
	const std::string controllerAgentName = config.at("playerName");
	/*
	auto test = GameManager::Instance();
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
	*/
}

void PlayerMovement::MoveLeft() {
}

void PlayerMovement::MoveRight() {
}

void PlayerMovement::MoveUp() {
}

void PlayerMovement::MoveDown() {
}
