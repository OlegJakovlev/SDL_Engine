#pragma once

#ifndef TimerComponent_H
#define TimerComponent_H

#include "../../Engine/Component/AbstractComponent.h"
#include "TimerComponentModel/TimerComponentModel.h"
#include "TimerComponentView/TimerComponentView.h"
#include "../../Engine/Logger/Logger.h"
#include "../../Engine/Timer/Timer.h"

class TimerComponent : public AbstractComponent {
public:
	~TimerComponent();

	void Init() override;
	void LoadConfig(const nlohmann::json& config) override;
	void Update() override;
	void Render() override;

	void AddGamePlayTime();
private:
	TimerComponentModel* model;
	TimerComponentView* view;

	Timer* levelTimer;
	double startTime;
};

#endif