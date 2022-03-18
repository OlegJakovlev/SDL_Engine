#include "Engine/Configurator/SceneConfigurator/SceneConfigurator.h"
#include "Engine/GameManager.h"

int main(int argc, char* args[])
{
	// Load scenes data
	SceneConfigurator* sceneConfig = new SceneConfigurator("./Resources/Configurations/SceneConfiguration/example.json");
	sceneConfig->LoadConfiguration();

	// Create game resources
	GameManager* game = GameManager::Instance();
	game->Init();

	// Start the game
	game->Run();

	// Release resources
	GameManager::Release();
	game = nullptr;

	return 0;
}