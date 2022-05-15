#pragma once

#ifndef GameLoopView_H
#define GameLoopView_H

#include "../Engine/Component/AbstractComponent.h"
#include "../Engine/Component/TextComponent/TextComponent.h"

class GameLoopView : public AbstractComponent {
public:
	~GameLoopView();

	void Init() override;

	void SetInputTextPointer(TextComponent* source);
	void SetUpdateTextPointer(TextComponent* source);
	void SetRenderTextPointer(TextComponent* source);

	void SetInputPerformaceText(const std::string& newText);
	void SetUpdatePerformaceText(const std::string& newText);
	void SetRenderPerformaceText(const std::string& newText);

private:
	TextComponent* inputPerformanceText;
	TextComponent* updatePerformanceText;
	TextComponent* renderPerformanceText;
};

#endif