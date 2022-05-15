#include <chrono>
#include <thread>
#include "Engine/Configurator/SceneConfigurator/SceneConfigurator.h"
#include "Engine/Configurator/AudioConfigurator/AudioConfigurator.h"
#include "Engine/GameManager.h"

int main(int argc, char* args[])
{
	// Load configurators
	SceneConfigurator* sceneConfig = new SceneConfigurator("Resources/Configurations/SceneConfiguration/example.json");
	sceneConfig->LoadConfiguration();

	AudioConfigurator* audioConfig = new AudioConfigurator("Resources/Configurations/AudioConfiguration/example.json");
	audioConfig->LoadConfiguration();

	// Create game resources
	GameManager* game = GameManager::Instance();
	game->Init(sceneConfig->GetSceneManager());

	// Start the game
	game->Run();

	// Release resources
	GameManager::Release();
	game = nullptr;

	// Release configurators
	delete audioConfig;
	delete sceneConfig;
	
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Logger::Instance().LogMessage("Application closed!");

	return 0;
}