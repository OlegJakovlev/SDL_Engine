#include "Engine/GameManager.h"

int main(int argc, char* args[])
{
	// Create game resources
	GameManager* game = GameManager::Instance();

	// Start the game
	game->Run();

	// Release resources
	GameManager::Release();
	game = nullptr;

	return 0;
}