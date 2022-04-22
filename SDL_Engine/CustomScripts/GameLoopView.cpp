#include "GameLoopView.h"

void GameLoopView::Render() {
	inputPerformanceText->Render();
	updatePerformanceText->Render();
	renderPerformanceText->Render();
}

void GameLoopView::SetInputPerformaceText(const std::string& newText) {
	inputPerformanceText->SetText(newText);
}

void GameLoopView::SetUpdatePerformaceText(const std::string& newText) {
	updatePerformanceText->SetText(newText);
}

void GameLoopView::SetRenderPerformaceText(const std::string& newText) {
	renderPerformanceText->SetText(newText);
}
