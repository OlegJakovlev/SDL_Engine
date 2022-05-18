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

	virtual void AdjustHealth(int healthAdjustment);

protected:
	HealthComponentModel* model;
	HealthComponentView* view;

	bool viewNeeded;
};

#endif