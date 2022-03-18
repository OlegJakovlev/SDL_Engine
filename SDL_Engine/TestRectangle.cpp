#include "TestRectangle.h"

TestRectangle::TestRectangle() : GameObject() {
    rectangle.w = 200;
    rectangle.h = 200;
}

void TestRectangle::Render(Graphics* graphics) {
    SDL_SetRenderDrawColor(graphics->GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRects(graphics->GetRenderer(), &rectangle, 1);
    SDL_SetRenderDrawColor(graphics->GetRenderer(), 0, 0, 0, 255);
}

void TestRectangle::Update() {
    rectangle.x = position.GetX();
    rectangle.y = position.GetY();

    //position.SetX(position.GetX() + 1);
    //position.SetY(position.GetY() + 1);
}

