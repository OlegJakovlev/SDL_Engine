#include "Vector2.h"

template<>
Vector2<float>::Vector2() {
    SetX(0);
    SetY(0);
}

template<>
Vector2<int>::Vector2() {
    SetX(0);
    SetY(0);
}

template<class T>
Vector2<T>::Vector2(T newX, T newY) {
    SetX(newX);
    SetY(newY);
}

template<class T>
void Vector2<T>::SetX(T newX) {
    x = newX;
}

template<class T>
void Vector2<T>::SetY(T newY) {
    y = newY;
}

template<>
float Vector2<float>::GetX() {
    return x;
}

template<>
int Vector2<int>::GetX() {
    return x;
}

template<>
float Vector2<float>::GetY() {
    return y;
}

template<>
int Vector2<int>::GetY() {
    return y;
}