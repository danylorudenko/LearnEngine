#include "..\Include\Math\Vector2.h"

#include <cmath>

Vector2::Vector2(float x, float y) :
	x_(x), y_(y)
{

}

Vector2::Vector2(float val) :
	x_(val), y_(val)
{

}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(rhs.x_ + x_, rhs.y_ + y_);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x_ - rhs.x_, y_ - rhs.y_);
}

Vector2 Vector2::operator*(float rhs) const
{
	return Vector2(x_ * rhs, y_ * rhs);
}

Vector2 Vector2::operator/(float rhs) const
{
	return Vector2(x_ / rhs, y_ / rhs);
}

float Vector2::Length() const
{
	return std::sqrtf(x_ * x_ + y_ * y_);
}

Vector2& Vector2::Normalize()
{
	float length = this->Length();
	x_ /= length;
	y_ /= length;
	return *this;
}

float Vector2::Dot(const Vector2& rhs) const
{
	return (x_ * rhs.x_) + (y_ * rhs.y_);
}

float Vector2::Cross(const Vector2& rhs) const
{
	return (x_ * rhs.y_ - y_ * rhs.x_);
}

Vector2 Vector2::Projection(const Vector2& target) const
{
	return (target * (this->Dot(target) / std::pow(target.Length(), 2)));
}