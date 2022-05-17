#pragma once

#ifndef ScoreComponent_H
#define ScoreComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "ScoreComponentModel/ScoreComponentModel.h"
#include "ScoreComponentView/ScoreComponentView.h"
#include "../../Engine/Logger/Logger.h"
#include "../../Engine/Timer/Timer.h"
#include "../../Engine/GameData/GameData.h"

class ScoreComponent : public AbstractComponent {
public:
	~ScoreComponent();

	void Init() override;
	void LoadConfig(const nlohmann::json& config) override;
	void Update() override;
	void Render() override;

	void AdjustScore(int scoreAdjustment);

	void TurnOnMultiplier(double duration);
	void TurnOffMultiplier();
private:
	ScoreComponentModel* model;
	ScoreComponentView* view;

	bool multiplierStatus = false;
	double multiplierDuration;

	Timer timer;
	double multiplierTimer;
};

#endif