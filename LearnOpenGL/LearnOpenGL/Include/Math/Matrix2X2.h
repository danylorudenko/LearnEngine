#ifndef __MATRIX_2X2_H__
#define __MATRIX_2X2_H__

#include "..\Include\Math\Vector2.h"

class Matrix2X2
{
public:
	Matrix2X2						(const Vector2& R1, const Vector2& R2);
	Matrix2X2						(Vector2&& R1, Vector2&& R2);
	Matrix2X2						(float R1C1, float R1C2, float R2C1, float R2C2);

	Matrix2X2						(const Matrix2X2& rhs) = default;
	Matrix2X2&		operator=		(const Matrix2X2& rhs) = default;

	Matrix2X2						(Matrix2X2&& rhs) = default;
	Matrix2X2&		operator=		(Matrix2X2&& rhs) = default;

	Vector2			C1				() const;
	Vector2			C2				() const;

	Vector2			SetC1			(const Vector2& C1);
	Vector2			SetC2			(const Vector2& C2);

	Vector2 R1_;
	Vector2 R2_;
};

Vector2			operator*		(const Vector2& lhs, const Matrix2X2& rhs);

Matrix2X2		operator*		(const Matrix2X2& lhs, const Matrix2X2& rhs);

#endif