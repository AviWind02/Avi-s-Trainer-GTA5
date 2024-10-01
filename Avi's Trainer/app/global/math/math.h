#pragma once
namespace app {
    namespace math {

        float Length(Vector3 vec);
        Vector3 Add(Vector3 left, Vector3 right);
        Vector3 Subtract(Vector3 left, Vector3 right);
        Vector3 Multiply(Vector3 value, float scale);
        Vector3 Modulate(Vector3 left, Vector3 right);
        Vector3 Divide(Vector3 value, float scale);
        Vector3 DegreeToRadian(const Vector3& angles);
        Vector3 Reflect(Vector3 vector, Vector3 normal);
        Vector3 RotationToDirection(Vector3* rotation);

        Vector3 operator * (const float& scale, const Vector3& value);
        Vector3 operator - (const Vector3& left, const Vector3& right);
        Vector3 operator * (const Vector3& value, const float& scale);
        Vector3 operator + (const Vector3& left, const Vector3& right);

        Vector2 Add(const Vector2& left, const Vector2& right);
        Vector2 Subtract(const Vector2& left, const Vector2& right);
        Vector2 Multiply(const Vector2& value, const float& scale);
        Vector2 Modulate(const Vector2& left, const Vector2& right);
        Vector2 Divide(const Vector2& value, const float& scale);
        Vector2 Reflect(const Vector2& vector, const Vector2& normal);

        Vector2 operator + (const Vector2& left, const Vector2& right);
        Vector2 operator - (const Vector2& left, const Vector2& right);
        Vector2 operator - (const Vector2& value);
        Vector2 operator * (const Vector2& vec, const float& scale);
        Vector2 operator * (const float& scale, const Vector2& vec);
        Vector2 operator / (const Vector2& vec, const float& scale);

        float CalculateDistance(Vector3* pointA, Vector3* pointB);
        float DegreeToRadian(float angle);
        float RadianToDegree(float angle);
        int get_random_int_in_range(int min, int max);
        float get_random_float_in_range(float min, float max);

    }
}
