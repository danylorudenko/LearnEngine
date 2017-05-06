#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2
{
public:
	Vector2					() = default;

	Vector2					(const Vector2& rhs) = default;
	Vector2&	operator=	(const Vector2& rhs) = default;

	Vector2					(Vector2&& rhs) = default;
	Vector2&	operator=	(Vector2&& rhs) = default;

	Vector2					(float x, float y);
	explicit Vector2		(float val);

	Vector2		operator+	(const Vector2& rhs) const;
	Vector2		operator-	(const Vector2& rhs) const;
	Vector2		operator*	(float rhs) const;
	Vector2		operator/	(float rhs) const;

	float		Length		() const;
	Vector2&	Normalize	();
	float		Dot			(const Vector2& rhs) const;
	float		Cross		(const Vector2& rhs) const;

	Vector2		Projection	(const Vector2& target) const;


	float x_;
	float y_;
};

#endif