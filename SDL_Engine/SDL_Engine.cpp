#include "Engine/GameManager.h"

int main(int argc, char* args[])
{
	// Create configurators and load configs

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