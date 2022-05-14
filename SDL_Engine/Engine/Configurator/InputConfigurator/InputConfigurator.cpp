#include "InputConfigurator.h"
#include "../../GameManager.h"

InputConfigurator::InputConfigurator(const std::string& configPath) : Configurator(configPath) {
}

InputConfigurator::~InputConfigurator() {
	delete inputController;
	inputController = nullptr;
}

void InputConfigurator::LoadConfiguration() {
	Configurator::LoadConfiguration();

	inputController = new InputController();

	for (auto& typeOfControl : configuration.items()) {
		for (auto& keyBind : configuration.at(typeOfControl.key()).items()) {
			std::string actionName = keyBind.key();

			// http://www.wesnoth.org/devdocs/keyboard_8cpp_source.html
			SDL_Scancode bindKey = SDL_GetScancodeFromName(keyBind.value().get<std::string>().c_str());

			if (bindKey == SDL_SCANCODE_UNKNOWN) {
				InputLogger::Instance().LogError("Key Bind for `" + actionName + "` action is not valid!");
				continue;
			}
			else {
				InputLogger::Instance().LogMessage("Key Bind for `" + actionName + "` action is created!");
			}

			inputController->CreateAction(actionName, bindKey);
		}
	}
}

void InputConfigurator::Initialize() {
	inputController->LinkAction("toggleFullScreenMode", std::bind(&Graphics::ToggleFullScreen, Graphics::Instance()));
	
	inputController->LinkAction("toggleInput", std::bind(&GameLoop::ToggleInput, GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()));
	inputController->LinkAction("toggleUpdate", std::bind(&GameLoop::ToggleUpdate, GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()));
	inputController->LinkAction("toggleRender", std::bind(&GameLoop::ToggleRender, GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetGameLoop()));

	inputController->LinkAction("toggleSoundEffects", std::bind(&Audio::ToggleSoundEffects, AudioLocator::GetAudio()));
	inputController->LinkAction("toggleMusicEffects", std::bind(&Audio::ToggleMusicEffects, AudioLocator::GetAudio()));

	inputController->LinkAction("increaseSoundLevel", std::bind(&Audio::IncreaseSoundVolume, AudioLocator::GetAudio()));
	inputController->LinkAction("decreaseSoundLevel", std::bind(&Audio::DecreaseSoundVolume, AudioLocator::GetAudio()));

	inputController->LinkAction("increaseMusicLevel", std::bind(&Audio::IncreaseMusicVolume, AudioLocator::GetAudio()));
	inputController->LinkAction("decreaseMusicLevel", std::bind(&Audio::DecreaseMusicVolume, AudioLocator::GetAudio()));

	inputController->LinkAction("loadNextScene", std::bind(&SceneManager::LoadNextScene, GameManager::Instance()->GetSceneManager()));
}

InputController* InputConfigurator::GetInputController() {
	return inputController;
}