#include "pch.h"

namespace app {

	namespace math
	{

		float Length(Vector3 vec) {
			return static_cast<float>(sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
		}
		Vector3 Add(Vector3 left, Vector3 right) {
			return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
		}
		Vector3 Subtract(Vector3 left, Vector3 right) {
			return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
		}
		Vector3 Multiply(Vector3 value, float scale) {
			return Vector3(value.x * scale, value.y * scale, value.z * scale);
		}
		Vector3 Modulate(Vector3 left, Vector3 right) {
			return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
		}
		Vector3 Divide(Vector3 value, float scale) {
			return Vector3(value.x / scale, value.y / scale, value.z / scale);
		}
		Vector3 DegreeToRadian(const Vector3& angles) {
			return Vector3(angles.x * 0.0174532925199433F, angles.y * 0.0174532925199433F, angles.z * 0.0174532925199433F);
		}
		Vector3 Reflect(Vector3 vector, Vector3 normal) {
			Vector3 result{ 0, 0, 0 };
			float dot = ((vector.x * normal.x) + (vector.y * normal.y)) + (vector.z * normal.z);

			result.x = vector.x - ((2.0f * dot) * normal.x);
			result.y = vector.y - ((2.0f * dot) * normal.y);
			result.z = vector.z - ((2.0f * dot) * normal.z);

			return result;
		}
		Vector3 RotationToDirection(Vector3* rotation) {
			float radiansZ = rotation->z * 0.0174532924f;
			float radiansX = rotation->x * 0.0174532924f;
			float cosX = cos(radiansX);
			float sinZ = sin(radiansZ);
			float cosZ = cos(radiansZ);
			float sinX = sin(radiansX);
			float cosXAbs = abs(cosX);

			Vector3 direction{ 0, 0, 0 };
			direction.x = -sinZ * cosXAbs;
			direction.y = cosZ * cosXAbs;
			direction.z = sinX;

			return direction;
		}
		Vector3 operator * (float const& scale, Vector3 const& value) {
			return Vector3{ value.x * scale, value.y * scale, value.z * scale };
		}
		Vector3 operator - (Vector3 const& left, Vector3 const& right) {
			return Vector3{ left.x - right.x, left.y - right.y, left.z - right.z };
		}
		Vector3 operator * (Vector3 const& value, float const& scale) {
			return Vector3{ value.x * scale, value.y * scale, value.z * scale };
		}
		Vector3 operator + (Vector3 const& left, Vector3 const& right) {
			return Vector3{ left.x + right.x, left.y + right.y, left.z + right.z };
		}


		Vector2 Add(Vector2 const& left, Vector2 const& right) {
			return Vector2(left.x + right.x, left.y + right.y);
		}
		Vector2 Subtract(Vector2 const& left, Vector2 const& right) {
			return Vector2(left.x - right.x, left.y - right.y);
		}
		Vector2 Multiply(Vector2 const& value, float const& scale) {
			return Vector2(value.x * scale, value.y * scale);
		}
		Vector2 Modulate(Vector2 const& left, Vector2 const& right) {
			return Vector2(left.x * right.x, left.y * right.y);
		}
		Vector2 Divide(Vector2 const& value, float const& scale) {
			return Vector2(value.x / scale, value.y / scale);
		}
		Vector2 Reflect(Vector2 const& vector, Vector2 const& normal) {
			Vector2 result{ 0, 0 };
			float dot = ((vector.x * normal.x) + (vector.y * normal.y));

			result.x = vector.x - ((2.0f * dot) * normal.x);
			result.y = vector.y - ((2.0f * dot) * normal.y);

			return result;
		}
		Vector2 operator + (Vector2 const& left, Vector2 const& right) {
			return Vector2(left.x + right.x, left.y + right.y);
		}
		Vector2 operator - (Vector2 const& left, Vector2 const& right) {
			return Vector2(left.x - right.x, left.y - right.y);
		}
		Vector2 operator - (Vector2 const& value) {
			return Vector2(-value.x, -value.y);
		}
		Vector2 operator * (Vector2 const& vec, float const& scale) {
			return Vector2(vec.x * scale, vec.y * scale);
		}
		Vector2 operator * (float const& scale, Vector2 const& vec) {
			return vec * scale;
		}
		Vector2 operator / (Vector2 const& vec, float const& scale) {
			return Vector2(vec.x / scale, vec.y / scale);
		}



		float CalculateDistance(Vector3* pointA, Vector3* pointB) {
			float dx = pointB->x - pointA->x;
			float dy = pointB->y - pointA->y;
			float dz = pointB->z - pointA->z;
			return sqrt(dx * dx + dy * dy + dz * dz);
		}
		float DegreeToRadian(float angle) {
			return angle * 0.0174532925199433F;
		}
		float RadianToDegree(float angle) {
			return angle / 0.0174532925199433F;
		}
		int get_random_int_in_range(int min, int max) {
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> u(min, max);
			return u(rng);
		}
		float get_random_float_in_range(float min, float max) {
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_real_distribution<float> u(min, max);
			return u(rng);
		}

	}
}