#include "ScoreComponentModel.h"

void ScoreComponentModel::AddScore(unsigned int points) {
    score += points;
}

void ScoreComponentModel::SubstractScore(unsigned int points) {
    score -= points;
}

unsigned int ScoreComponentModel::GetScore() const {
    return score;
}
