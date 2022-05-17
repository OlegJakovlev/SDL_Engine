#include "WinnerView.h"
#include "../../Engine/GameObject/GameObject.h"

void WinnerView::Init() {
    // Get reference to text components
    winnerText = static_cast<TextComponent*>(
        objectLinkedTo->FindChildGameObjectByName("Winner Text")->GetComponent("Text")
    );

    int player1Score = stoi(GameData::Instance()->GetDataEntry("Player1"));
    int player2Score = stoi(GameData::Instance()->GetDataEntry("Player2"));

    std::string text;
    if (player1Score != player2Score) {
        text = std::string() + ((player1Score > player2Score) ? "Player 1" : "Player 2") + " WON!";
    }
    else {
        text = "DRAW!";
    }

    // Set static text
    winnerText->SetText(text);
    AudioLocator::GetAudio()->PlayMusic("winnerMusic");
}