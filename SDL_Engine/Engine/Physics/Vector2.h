#pragma once

#ifndef Vector2_H
#define Vector2_H

#include <nlohmann/json.hpp>

namespace Vector2 {
    template <class T>
    class Vector2 {
    public:
        Vector2();
        Vector2(T newX, T newY);
        ~Vector2() = default;

        const T GetX() const;
        const T GetY() const;
        void SetX(T newX);
        void SetY(T newY);

    private:
        T x;
        T y;
    };

    template <class T>
    void to_json(nlohmann::json& json, const Vector2<T>& objectToConvert);

    template <class T>
    void from_json(const nlohmann::json& json, Vector2<T>& objectToConvert);
}

#endif
