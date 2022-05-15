#pragma once

#ifndef Vector2_H
#define Vector2_H

#include <nlohmann/json.hpp>

namespace Vector2 {
    template <class T>
    struct Vector2 {
    public:
        Vector2();
        Vector2(T newX, T newY);
        Vector2(const Vector2& other);
        ~Vector2() = default;

        float FastSquareRoot(float magnitude);
        float GetMagnitude();

        Vector2<float> Normalize();
        static float DotProduct(const Vector2<T>& lhs, const Vector2<T>& rhs);

        Vector2<T>& operator+=(const Vector2<T>& rhs);
        Vector2<T>& operator-=(const Vector2<T>& rhs);
        Vector2<T>& operator*=(T value);
        bool operator==(const Vector2<T>& rhs);

        Vector2<T> operator+(const Vector2<T>& rhs);
        Vector2<T> operator-(const Vector2<T>& rhs);
        Vector2<T> operator*(T value);

        T x;
        T y;
    };

    template <class T>
    void to_json(nlohmann::json& json, const Vector2<T>& objectToConvert);

    template <class T>
    void from_json(const nlohmann::json& json, Vector2<T>& objectToConvert);
}

#endif
