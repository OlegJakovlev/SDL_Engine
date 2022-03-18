#pragma once

#ifndef TestRectangle_H
#define TestRectangle_H

#include "Engine/GameObject/GameObject.h"
#include <SDL_rect.h>

class TestRectangle : public GameObject {
public:
    TestRectangle();
    void Render(Graphics* graphics) override;
    void Update() override;

private:
    SDL_Rect rectangle;
};

#endif
