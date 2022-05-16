#include "MenuView.h"
#include "../../Engine/GameManager.h"

void MenuView::Init() {
    // Get reference to text components
    titleText = static_cast<TextComponent*>(
        objectLinkedTo->FindChildGameObjectByName("Game Title")->GetComponent("Text")
    );

    engineControlsText = static_cast<TextComponent*>(
        objectLinkedTo->FindChildGameObjectByName("Engine Controls")->GetComponent("Text")
    );

    gameplayControlsText = static_cast<TextComponent*>(
        objectLinkedTo->FindChildGameObjectByName("Game Controls")->GetComponent("Text")
    );

    // Get menu controls
    InputController* menuControls = GameManager::Instance()->GetSceneManager()->GetCurrentScene()->GetInputConfigurator()->GetInputController();
    
    // Get in game controls
    InputConfigurator* inGameInputConfigurator = new InputConfigurator("Resources/Configurations/InputConfiguration/game.json");
    inGameInputConfigurator->LoadConfiguration();
    inGameInputConfigurator->Initialize();
    InputController* inGameControls = inGameInputConfigurator->GetInputController();

    // Get text for componenets
    engineControls = std::string() + 
        "Toggle Full Screen: " + menuControls->GetEventBindedKeyName("toggleFullScreenMode") + "\n\n" +
        "Toggle Input: " + menuControls->GetEventBindedKeyName("toggleInput") + "\n" +
        "Toggle Update: " + menuControls->GetEventBindedKeyName("toggleUpdate") + "\n" +
        "Toggle Render: " + menuControls->GetEventBindedKeyName("toggleRender") + "\n\n" +
        "Toggle Sound Effect: " + menuControls->GetEventBindedKeyName("toggleSoundEffects") + "\n" +
        "Increase Sound Level: " + menuControls->GetEventBindedKeyName("increaseSoundLevel") + "\n" +
        "Decrease Sound Level: " + menuControls->GetEventBindedKeyName("decreaseSoundLevel") + "\n\n" +
        "Toggle Music Effect: " + menuControls->GetEventBindedKeyName("toggleMusicEffects") + "\n" +
        "Increase Music Level: " + menuControls->GetEventBindedKeyName("increaseMusicLevel") + "\n" +
        "Decrease Music Level: " + menuControls->GetEventBindedKeyName("decreaseMusicLevel");

    gameControls = std::string() +
        "Player 1:\n" +
        "Move Up : " + inGameControls->GetEventBindedKeyName("player1MoveUp") + "\n" +
        "Move Down: " + inGameControls->GetEventBindedKeyName("player1MoveDown") + "\n" +
        "Move Left: " + inGameControls->GetEventBindedKeyName("player1MoveLeft") + "\n" +
        "Move Right: " + inGameControls->GetEventBindedKeyName("player1MoveRight") + "\n\n" +
        "Player 2:\n" +
        "Move Up: " + inGameControls->GetEventBindedKeyName("player2MoveUp") + "\n" +
        "Move Down: " + inGameControls->GetEventBindedKeyName("player2MoveDown") + "\n" +
        "Move Left: " + inGameControls->GetEventBindedKeyName("player2MoveLeft") + "\n" +
        "Move Right: " + inGameControls->GetEventBindedKeyName("player2MoveRight") + "\n";
    
    delete inGameInputConfigurator;

    // Set static text
    titleText->SetText(title);
    engineControlsText->SetText(engineControls);
    gameplayControlsText->SetText(gameControls);

    AudioLocator::GetAudio()->PlayMusic("background");
}

void MenuView::LoadConfig(const nlohmann::json& config) {
    title = config.value("title", "");
}
