#include "GameLoopView.h"
#include "../Engine/GameManager.h"

GameLoopView::~GameLoopView() {
	inputPerformanceText = nullptr;
	updatePerformanceText = nullptr;
	renderPerformanceText = nullptr;
}

void GameLoopView::Init() {
	Scene* currentScene = GameManager::Instance()->GetSceneManager()->GetCurrentScene();

	SetInputTextPointer(static_cast<TextComponent*>(
		currentScene->GetSceneObjectByID(6)->GetComponent("Text"))
	);

	SetUpdateTextPointer(static_cast<TextComponent*>(
		currentScene->GetSceneObjectByID(7)->GetComponent("Text"))
	);

	SetRenderTextPointer(static_cast<TextComponent*>(
		currentScene->GetSceneObjectByID(8)->GetComponent("Text"))
	);
}

void GameLoopView::Render() {
	inputPerformanceText->Render();
	updatePerformanceText->Render();
	renderPerformanceText->Render();
}

void GameLoopView::SetInputTextPointer(TextComponent* source) {
	inputPerformanceText = source;
}

void GameLoopView::SetUpdateTextPointer(TextComponent* source) {
	updatePerformanceText = source;
}

void GameLoopView::SetRenderTextPointer(TextComponent* source) {
	renderPerformanceText = source;
}

void GameLoopView::SetInputPerformaceText(const std::string& newText) {
	inputPerformanceText->SetText("Input Time:" + newText);
}

void GameLoopView::SetUpdatePerformaceText(const std::string& newText) {
	updatePerformanceText->SetText("Update Time:" + newText);
}

void GameLoopView::SetRenderPerformaceText(const std::string& newText) {
	renderPerformanceText->SetText("Render Time:" + newText);
}
