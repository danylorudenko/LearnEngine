#include "..\Include\Math\Matrix2X2.h"

Matrix2X2::Matrix2X2(const Vector2& R1, const Vector2& R2) :
	R1_(R1), R2_(R2)
{

}

Matrix2X2::Matrix2X2(float R1C1, float R1C2, float R2C1, float R2C2)
	: R1_(R1C1, R1C2), R2_(R2C1, R2C2)
{

}

Matrix2X2::Matrix2X2(Vector2&& R1, Vector2&& R2) :
	R1_(R1), R2_(R2)
{

}

Vector2 Matrix2X2::C1() const
{
	return Vector2(R1_.x_, R2_.x_);
}

Vector2 Matrix2X2::C2() const
{
	return Vector2(R1_.y_, R2_.y_);
}

Vector2 Matrix2X2::SetC1(const Vector2& C1)
{
	R1_.x_ = C1.x_;
	R2_.x_ = C1.y_;

	return this->C1();
}

Vector2 Matrix2X2::SetC2(const Vector2& C2)
{
	R1_.y_ = C2.x_;
	R2_.y_ = C2.y_;

	return this->C2();
}

Vector2 operator*(const Vector2& lhs, const Matrix2X2& rhs)
{
	return Vector2(lhs.Dot(rhs.C1()), lhs.Dot(rhs.C2()));
}

Matrix2X2 operator*(const Matrix2X2& lhs, const Matrix2X2& rhs)
{
	return Matrix2X2(
		Vector2(lhs.R1_.Dot(rhs.C1()), lhs.R1_.Dot(rhs.C2())),
		Vector2(lhs.R2_.Dot(rhs.C1()), lhs.R2_.Dot(rhs.C2()))
	);
}