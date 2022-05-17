#pragma once

#ifndef HealthComponent_H
#define HealthComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "HealthComponentModel/HealthComponentModel.h"
#include "HealthComponentView/HealthComponentView.h"
#include "../../Engine/Timer/Timer.h"

class HealthComponent : public AbstractComponent {
public:
	~HealthComponent();

	void Init() override;
	void LoadConfig(const nlohmann::json& config) override;
	void Render() override;

	void AdjustHealth(int healthAdjustment);

private:
	HealthComponentModel* model;
	HealthComponentView* view;

	Timer timer;
	double lastTimeDamaged;
	double invincibilityTime;
};

#endif