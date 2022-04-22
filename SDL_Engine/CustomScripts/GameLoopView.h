#pragma once

#ifndef GameLoopView_H
#define GameLoopView_H

#include "../Engine/Component/IComponent.h"
#include "../Engine/Component/TextComponent/TextComponent.h"

class GameLoopView : public IComponent {
public:
	void Render() override;

	void SetInputPerformaceText(const std::string& newText);
	void SetUpdatePerformaceText(const std::string& newText);
	void SetRenderPerformaceText(const std::string& newText);

private:
	TextComponent* inputPerformanceText;
	TextComponent* updatePerformanceText;
	TextComponent* renderPerformanceText;
};

#endif