#pragma once

#ifndef HealthComponentModel_H
#define HealthComponentModel_H

class HealthComponentModel {
public:
    void AddHealth(unsigned int points);
    void SubstractHealth(unsigned int points);

    unsigned int GetHealth() const;

private:
    unsigned int health = 0;
};

#endif