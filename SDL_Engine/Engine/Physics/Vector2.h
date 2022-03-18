#pragma once

#ifndef Vector2_H
#define Vector2_H

template <class T>
class Vector2 {
public:
    Vector2();
    Vector2(T newX, T newY);

    void SetX(T newX);
    void SetY(T newY);

    T GetX();
    T GetY();

private:
    T x;
    T y;
};

#endif
