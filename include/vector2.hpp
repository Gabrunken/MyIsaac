#pragma once

class Vector2
{
public:
	constexpr Vector2(float xValue, float yValue) noexcept : x(xValue), y(yValue) {};
	constexpr Vector2(float value) noexcept : x(value), y(value) {};
	constexpr Vector2(const Vector2& vector) noexcept : x(vector.x), y(vector.y) {};
	constexpr Vector2() noexcept = default;
	constexpr ~Vector2() noexcept = default;

	constexpr Vector2& operator+=(const Vector2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	constexpr Vector2& operator-=(const Vector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	constexpr Vector2& operator*=(const Vector2& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2& operator/=(const Vector2& other) noexcept;

	constexpr Vector2& operator+=(float value) noexcept
	{
		x += value;
		y += value;
		return *this;
	}

	constexpr Vector2& operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		return *this;
	}

	constexpr Vector2& operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}

	Vector2& operator/=(float value) noexcept;

	[[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const noexcept
	{
		Vector2 result(*this);
		result += other;
		return result;
	}

	[[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const noexcept
	{
		Vector2 result(*this);
		result -= other;
		return result;
	}

	[[nodiscard]] constexpr Vector2 operator*(const Vector2& other) const noexcept
	{
		Vector2 result(*this);
		result *= other;
		return result;
	}

	[[nodiscard]] Vector2 operator/(const Vector2& other) const noexcept;

	[[nodiscard]] constexpr Vector2 operator+(float value) const noexcept
	{
		Vector2 result(*this);
		result += value;
		return result;
	}

	[[nodiscard]] constexpr Vector2 operator-(float value) const noexcept
	{
		Vector2 result(*this);
		result -= value;
		return result;
	}

	[[nodiscard]] constexpr Vector2 operator*(float value) const noexcept
	{
		Vector2 result(*this);
		result *= value;
		return result;
	}

	[[nodiscard]] Vector2 operator/(float value) const noexcept;

	//Get the length of this vector.
	float GetLength() const noexcept;
	//Normalize this vector.
	void Normalize() noexcept;
	//Get a copy of this vector normalized without changing itself.
	Vector2 GetNormalized() const noexcept;

	static float Distance(const Vector2& first, const Vector2& second) noexcept;
	//The distance still squared is useful for distance checks (is 'a' close to 'b'?).
	//This function is faster so if the actual distance is needed then use 'Distance'.
	static constexpr float DistanceSquared(const Vector2& first, const Vector2& second) noexcept
	{
		float deltaX = second.x - first.x;
		float deltaY = second.y - first.y;

		return deltaX * deltaX + deltaY * deltaY;
	}

	static inline constexpr float Dot(const Vector2& first, const Vector2& second) noexcept
	{
		return first.x * second.x + first.y * second.y;
	}

	static constexpr Vector2 Up() noexcept    { return Vector2(0.0f, 1.0f); }
	static constexpr Vector2 Right() noexcept { return Vector2(1.0f, 0.0f); }
	static constexpr Vector2 Down() noexcept  { return Vector2(0.0f, -1.0f); }
	static constexpr Vector2 Left() noexcept  { return Vector2(-1.0f, 0.0f); }
public:
	float x = 0.0f, y = 0.0f;
private:
	constexpr static float epsilon = 1e-5f;
};