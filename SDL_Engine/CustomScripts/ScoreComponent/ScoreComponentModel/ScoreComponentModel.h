#pragma once

#ifndef ScoreComponentModel_H
#define ScoreComponentModel_H

class ScoreComponentModel {
public:
    void AddScore(unsigned int points);
    void SubstractScore(unsigned int points);

    unsigned int GetScore() const;

private:
    unsigned int score = 0;
};

#endif