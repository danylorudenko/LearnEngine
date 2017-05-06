#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
public:
	Vector3					() = default;

	Vector3					(const Vector3& rhs) = default;
	Vector3&	operator=	(const Vector3& rhs) = default;

	Vector3					(Vector3&& rhs) = default;
	Vector3&	operator=	(Vector3&& rhs) = default;

	Vector3					(float x, float y, float z);
	Vector3					(float val);

	Vector3		operator+	(const Vector3& rhs) const;
	Vector3		operator-	(const Vector3& rhs) const;
	Vector3		operator*	(float rhs) const;
	Vector3		operator/	(float rhs) const;

	float		Length		() const;
	void		Normalize	();
	float		Dot			(const Vector3& rhs) const;
	Vector3		Cross		(const Vector3& rhs) const;


	float x_;
	float y_;
	float z_;
};

#endif