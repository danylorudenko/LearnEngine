#include "..\Include\Triangle.h"

Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3) :
	v1_(v1), v2_(v2), v3_(v3)
{
	glGenBuffers(1, &VBO_);
}