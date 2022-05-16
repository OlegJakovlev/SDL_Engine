#include "WinnerView.h"
#include "../../Engine/GameObject/GameObject.h"

void WinnerView::Init() {
    // Get reference to text components
    winnerText = static_cast<TextComponent*>(
        objectLinkedTo->FindChildGameObjectByName("Winner Text")->GetComponent("Text")
    );

    int player1Score = stoi(GameData::Instance()->data.at("Player1"));
    int player2Score = stoi(GameData::Instance()->data.at("Player2"));

    // Set static text
    winnerText->SetText("");
    AudioLocator::GetAudio()->PlayMusic("background");
}