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

    template<>
    const int Vector2<int>::GetX() const {
        return x;
    }

    template<>
    const float Vector2<float>::GetX() const {
        return x;
    }

    template<>
    const int Vector2<int>::GetY() const {
        return y;
    }

    template<>
    const float Vector2<float>::GetY() const {
        return y;
    }

    template<class T>
    void Vector2<T>::SetX(T newX) {
        x = newX;
    }

    template<class T>
    void Vector2<T>::SetY(T newY) {
        y = newY;
    }

    template <>
    void to_json(nlohmann::json& json, const Vector2<int>& objectToConvert) {
        json = nlohmann::json{
            {"x", objectToConvert.GetX()},
            {"y", objectToConvert.GetY()}
        };
    }

    template <>
    void to_json(nlohmann::json& json, const Vector2<float>& objectToConvert) {
        json = nlohmann::json{
            {"x", objectToConvert.GetX()},
            {"y", objectToConvert.GetY()}
        };
    }

    template <>
    void from_json(const nlohmann::json& json, Vector2<int>& objectToConvert) {
        objectToConvert.SetX(json.at("x").get<int>());
        objectToConvert.SetY(json.at("y").get<int>());
    }

    template <>
    void from_json(const nlohmann::json& json, Vector2<float>& objectToConvert) {
        objectToConvert.SetX(json.at("x").get<float>());
        objectToConvert.SetY(json.at("y").get<float>());
    }
}