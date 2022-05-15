#pragma once

#ifndef ScoreComponent_H
#define ScoreComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "ScoreComponentModel/ScoreComponentModel.h"
#include "ScoreComponentView/ScoreComponentView.h"
#include "../../Engine/Logger/Logger.h"
#include "../../Engine/GameData/GameData.h"

class ScoreComponent : public AbstractComponent {
public:
	~ScoreComponent();

	void Init() override;
	void LoadConfig(const nlohmann::json& config) override;
	void Render() override;

	void AdjustScore(int scoreAdjustment);

private:
	ScoreComponentModel* model;
	ScoreComponentView* view;
};

#endif