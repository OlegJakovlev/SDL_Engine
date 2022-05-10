#include "Vector2.h"

namespace Vector2 {
    template<>
    Vector2<int>::Vector2() : Vector2(0, 0) {
    }

    template<>
    Vector2<float>::Vector2() : Vector2(0, 0) {
    }

    template<class T>
    Vector2<T>::Vector2(T newX, T newY) {
        x = newX;
        y = newY;
    }

    template<class T>
    Vector2<T>::Vector2(const Vector2& other){
        x = other.x;
        y = other.y;
    }

    // Original Quake3 algorithm
    template<class T>
    float Vector2<T>::FastSquareRoot(float magnitude) {
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = magnitude * 0.5F;
        y = magnitude;
        i = *(long*)&y; // evil floating point bit level hacking
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y)); // 1st iteration

        return y;
    }

    template<class T>
    float Vector2<T>::GetMagnitude() {
        return x * x + y * y;
    }

    template<>
    Vector2<int> Vector2<int>::Normalize() {
        Vector2 result;
        float inverseSquareRoot = FastSquareRoot(GetMagnitude());
        result.x = x * inverseSquareRoot;
        result.y = y * inverseSquareRoot;
        return result;
    }

    template<>
    Vector2<float> Vector2<float>::Normalize() {
        Vector2 result;
        float inverseSquareRoot = FastSquareRoot(GetMagnitude());
        result.x = x * inverseSquareRoot;
        result.y = y * inverseSquareRoot;
        return result;
    }

    template<>
    float Vector2<int>::DotProduct(const Vector2<int>& lhs, const Vector2<int>& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template<>
    Vector2<int>& Vector2<int>::operator+=(const Vector2<int>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<>
    Vector2<float>& Vector2<float>::operator+=(const Vector2<float>& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template<>
    Vector2<int>& Vector2<int>::operator-=(const Vector2<int>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<>
    Vector2<float>& Vector2<float>::operator-=(const Vector2<float>& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template<>
    Vector2<int> Vector2<int>::operator+(const Vector2<int>& rhs) {
        Vector2<int> result(*this);
        result += rhs;
        return result;
    }

    template<>
    Vector2<float> Vector2<float>::operator+(const Vector2<float>& rhs) {
        Vector2<float> result(*this);
        result += rhs;
        return result;
    }

    template<>
    Vector2<int> Vector2<int>::operator-(const Vector2<int>& rhs) {
        Vector2<int> result(*this);
        result -= rhs;
        return result;
    }

    template<>
    Vector2<float> Vector2<float>::operator-(const Vector2<float>& rhs) {
        Vector2<float> result(*this);
        result -= rhs;
        return result;
    }

    template<>
    float Vector2<float>::DotProduct(const Vector2<float>& lhs, const Vector2<float>& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template <>
    void to_json(nlohmann::json& json, const Vector2<int>& objectToConvert) {
        json = nlohmann::json{
            {"x", objectToConvert.x},
            {"y", objectToConvert.y}
        };
    }

    template <>
    void to_json(nlohmann::json& json, const Vector2<float>& objectToConvert) {
        json = nlohmann::json{
            {"x", objectToConvert.x},
            {"y", objectToConvert.y}
        };
    }

    template <>
    void from_json(const nlohmann::json& json, Vector2<int>& objectToConvert) {
        objectToConvert.x = json.at("x").get<int>();
        objectToConvert.y = json.at("y").get<int>();
    }

    template <>
    void from_json(const nlohmann::json& json, Vector2<float>& objectToConvert) {
        objectToConvert.x = json.at("x").get<float>();
        objectToConvert.y = json.at("y").get<float>();
    }
}