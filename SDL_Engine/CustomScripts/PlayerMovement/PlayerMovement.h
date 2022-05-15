#pragma once

#ifndef PlayerMovement_H
#define PlayerMovement_H

#include "../../Engine/Component/AbstractComponent.h"
#include "../../Engine/Component/AnimationComponent/AnimationComponent.h"
#include "../../Engine/Component/PhysicsComponent/PhysicsComponent.h"

class PlayerMovement : public AbstractComponent {
public:
	void Init() override;
	void LoadConfig(const nlohmann::json& config) override;
	void Update() override;

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

private:
	PhysicsComponent* physicsComponent;
	AnimationComponent* animationComponent;

	std::string controllerAgentName;

	Vector2::Vector2<int> movementDirection;
};

#endif