#include "..\Include\Math\Vector3.h"

#include <cmath>

Vector3::Vector3(float x, float y, float z) :
	x_(x), y_(y), z_(z)
{

}

Vector3::Vector3(float val) :
	x_(val), y_(val), z_(val)
{

}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(rhs.x_ + x_, rhs.y_ + y_, rhs.z_ + z_);
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
}

Vector3 Vector3::operator*(float rhs) const
{
	return Vector3(x_ * rhs, y_ * rhs, z_ * rhs);
}

Vector3 Vector3::operator/(float rhs) const
{
	return Vector3(x_ / rhs, y_ / rhs, z_ / rhs);
}

float Vector3::Length() const
{
	return std::sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
}

void Vector3::Normalize()
{
	float length = this->Length();
	x_ /= length;
	y_ /= length;
	z_ /= length;
}

float Vector3::Dot(const Vector3& rhs) const
{
	return (x_ * rhs.x_) + (y_ * rhs.y_) + (z_ * rhs.z_);
}

Vector3 Vector3::Cross(const Vector3& rhs) const
{
	return Vector3(y_ * rhs.z_ - z_ * rhs.y_, z_ * rhs.x_ - x_ * rhs.z_, x_ * rhs.y_ - y_ * rhs.x_);
}