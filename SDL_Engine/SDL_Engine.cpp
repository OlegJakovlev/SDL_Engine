#include <chrono>
#include <thread>
#include "Engine/Configurator/SceneConfigurator/SceneConfigurator.h"
#include "Engine/GameManager.h"
#include "Engine/Logger/SceneLogger/SceneLogger.h"

int main(int argc, char* args[])
{
	// Load configurators
	SceneConfigurator* sceneConfig = new SceneConfigurator("./Resources/Configurations/SceneConfiguration/example.json");
	sceneConfig->LoadConfiguration();

	Logger::Instance().LogError("1");

	/*
	// Create game resources
	GameManager* game = GameManager::Instance();
	game->Init();

	// Start the game
	game->Run();

	// Release resources
	GameManager::Release();
	game = nullptr;
	*/

	// Release configurators
	delete sceneConfig;
	
	std::cout << "Thanks for using our software...\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));

	return 0;
}