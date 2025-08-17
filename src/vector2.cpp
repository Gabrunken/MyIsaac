#include <vector2.hpp>
#include <cmath>

Vector2& Vector2::operator/=(const Vector2& other) noexcept
{
	if (std::fabs(other.x) <= epsilon)
		x = 0.0f;
	else x /= other.x;

	if (std::fabs(other.y) <= epsilon)
		y = 0.0f;
	else y /= other.y;
	
	return *this;
}

Vector2& Vector2::operator/=(float value) noexcept
{
	if (std::fabs(value) <= epsilon)
	{
		x = 0.0f;
		y = 0.0f;
		return *this;
	}

	x /= value;
	y /= value;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const noexcept
{
	Vector2 result(*this);
	result /= other;
	return result;
}

Vector2 Vector2::operator/(float value) const noexcept
{
	Vector2 result(*this);
	result /= value;
	return result;
}

float Vector2::GetLength() const noexcept
{
	return std::sqrt(x * x + y * y);
}

void Vector2::Normalize() noexcept
{
	float length = GetLength();

	if (std::fabs(length) <= epsilon)
	{
		x = 0.0f;
		y = 0.0f;
		return;
	}

	x /= length;
	y /= length;
}

Vector2 Vector2::GetNormalized() const noexcept
{
	Vector2 result = *this;
	float length = result.GetLength();

	if (std::fabs(length) <= epsilon)
	{
		return result;
	}

	result.x /= length;
	result.y /= length;

	return result;
}

float Vector2::Distance(const Vector2& first, const Vector2& second) noexcept
{
	float deltaX = second.x - first.x;
	float deltaY = second.y - first.y;

	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}