#pragma once

namespace core {
	class Vector2 {
	public:
		Vector2(float x, float y) : x(x), y(y) {}
	public:
		alignas(8) float x{};
		alignas(8) float y{};
	public:
		Vector2 operator*(const float amount) {
			return { x * amount, y * amount };
		}
		Vector2 operator*(const Vector2 vec) {
			return { x * vec.x, y * vec.y };
		}
		Vector2 operator/(const float amount) {
			return { x / amount, y / amount };
		}
		Vector2 operator/(const Vector2 vec) {
			return { x / vec.x, y / vec.y };
		}
		Vector2 operator+(const float amount) {
			return { x + amount, y + amount };
		}
		Vector2 operator+(const Vector2 vec) {
			return { x + vec.x, y + vec.y };
		}
		Vector2 operator-(const float amount) {
			return { x - amount, y - amount };
		}
		Vector2 operator-(const Vector2 vec) {
			return { x - vec.x, y - vec.y };
		}
		Vector2& operator+=(const float& amount) {
			x += amount;
			y += amount;
			return *this;
		}
		Vector2& operator+=(const Vector2& vec) {
			x += vec.x;
			y += vec.y;
			return *this;
		}
		Vector2& operator-=(const float& amount) {
			x -= amount;
			y -= amount;
			return *this;
		}
		Vector2& operator-=(const Vector2& vec) {
			x -= vec.x;
			y -= vec.y;
			return *this;
		}
		Vector2& operator/=(const float& amount) {
			x /= amount;
			y /= amount;
			return *this;
		}
		Vector2& operator/=(const Vector2& vec) {
			x /= vec.x;
			y /= vec.y;
			return *this;
		}
		Vector2& operator*=(const float& amount) {
			x *= amount;
			y *= amount;
			return *this;
		}
		Vector2& operator*=(const Vector2& vec) {
			x *= vec.x;
			y *= vec.y;
			return *this;
		}
	};

	class Vector3 {
	public:
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	public:
		alignas(8) float x{};
		alignas(8) float y{};
		alignas(8) float z{};
	public:
		Vector3 operator*(const float amount) {
			return { x * amount, y * amount, z * amount };
		}
		Vector3 operator*(const Vector3 vec) {
			return { x * vec.x, y * vec.y, z * vec.z };
		}
		Vector3 operator/(const float amount) {
			return { x / amount, y / amount, z / amount };
		}
		Vector3 operator/(const Vector3 vec) {
			return { x / vec.x, y / vec.y, z / vec.z };
		}
		Vector3 operator+(const float amount) {
			return { x + amount, y + amount, z + amount };
		}
		Vector3 operator+(const Vector3 vec) {
			return { x + vec.x, y + vec.y, z + vec.z };
		}
		Vector3 operator-(const float amount) {
			return { x - amount, y - amount, z - amount };
		}
		Vector3 operator-(const Vector3 vec) {
			return { x - vec.x, y - vec.y, z - vec.z };
		}
		Vector3& operator+=(const float& amount) {
			x += amount;
			y += amount;
			z += amount;
			return *this;
		}
		Vector3& operator+=(const Vector3& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}
		Vector3& operator-=(const float& amount) {
			x -= amount;
			y -= amount;
			z -= amount;
			return *this;
		}
		Vector3& operator-=(const Vector3& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			return *this;
		}
		Vector3& operator/=(const float& amount) {
			x /= amount;
			y /= amount;
			z /= amount;
			return *this;
		}
		Vector3& operator/=(const Vector3& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			return *this;
		}
		Vector3& operator*=(const float& amount) {
			x *= amount;
			y *= amount;
			z *= amount;
			return *this;
		}
		Vector3& operator*=(const Vector3& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			return *this;
		}
		bool operator==(const Vector3& vec) {
			return vec.x == x && vec.y == y && vec.z == z;
		}
		bool operator!=(const Vector3& vec) {
			return vec.x != x || vec.y != y || vec.z != z;
		}
	};

	class Vector4 {
	public:
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	public:
		alignas(8) float x{};
		alignas(8) float y{};
		alignas(8) float z{};
		alignas(8) float w{};
	public:
		Vector4 operator*(const float amount) {
			return { x * amount, y * amount, z * amount, w * amount };
		}
		Vector4 operator*(const Vector4 vec) {
			return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
		}
		Vector4 operator/(const float amount) {
			return { x / amount, y / amount, z / amount, w / amount };
		}
		Vector4 operator/(const Vector4 vec) {
			return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
		}
		Vector4 operator+(const float amount) {
			return { x + amount, y + amount, z + amount, w + amount };
		}
		Vector4 operator+(const Vector4 vec) {
			return { x + vec.x, y + vec.y, z + vec.z, w + vec.w };
		}
		Vector4 operator-(const float amount) {
			return { x - amount, y - amount, z - amount, w - amount };
		}
		Vector4 operator-(const Vector4 vec) {
			return { x - vec.x, y - vec.y, z - vec.z, w - vec.w };
		}
		Vector4& operator+=(const float& amount) {
			x += amount;
			y += amount;
			z += amount;
			w += amount;
			return *this;
		}
		Vector4& operator+=(const Vector4& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			return *this;
		}
		Vector4& operator-=(const float& amount) {
			x -= amount;
			y -= amount;
			z -= amount;
			w -= amount;
			return *this;
		}
		Vector4& operator-=(const Vector4& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
			return *this;
		}
		Vector4& operator/=(const float& amount) {
			x /= amount;
			y /= amount;
			z /= amount;
			w /= amount;
			return *this;
		}
		Vector4& operator/=(const Vector4& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			w /= vec.w;
			return *this;
		}
		Vector4& operator*=(const float& amount) {
			x *= amount;
			y *= amount;
			z *= amount;
			w *= amount;
			return *this;
		}
		Vector4& operator*=(const Vector4& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			w *= vec.w;
			return *this;
		}
	};
} // namespace core
