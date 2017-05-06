#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "..\Include\Math\Vector3.h"

#include <GL\glew.h>

class Triangle
{
public:
	Triangle							(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	
public:
	Vector3 v1_;
	Vector3 v2_;
	Vector3 v3_;

private:
	GLuint VBO_;
};

#endif