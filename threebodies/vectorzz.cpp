#include "vectorzz.h"
#include <cmath>


vectorzz::vectorzz()
{
}

vectorzz::vectorzz(double new_x = 0, double new_y = 0, double new_z = 0)
{
	this->x = new_x;
	this->y = new_y;
	this->z = new_z;
}

vectorzz::~vectorzz()
{
}

double vectorzz::modulus()
{
	return sqrt(x*x + y * y + z * z);
}

vectorzz operator+(const vectorzz &A, const vectorzz &B)
{
	vectorzz result(0, 0, 0);
	result.x = A.x + B.x;
	result.y = A.y + B.y;
	result.z = A.z + B.z;
	return result;
}

vectorzz operator-(const vectorzz &A, const vectorzz &B)
{
	vectorzz result(0, 0, 0);
	result.x = A.x - B.x;
	result.y = A.y - B.y;
	result.z = A.z - B.z;
	return result;
}

vectorzz operator*(double multi, const vectorzz &B)
{
	vectorzz result = vectorzz(0, 0, 0);
	result.x = multi * B.x;
	result.y = multi * B.y;
	result.z = multi * B.z;
	return result;
}

vectorzz operator/(const vectorzz &A, double para)
{
	vectorzz result = vectorzz(0, 0, 0);
	result.x = A.x / para;
	result.y = A.y / para;
	result.z = A.z / para;
	return result;
}
/*
vectorzz &vectorzz::operator+=(const vectorzz & B)
{
	vectorzz result(0, 0, 0);
	result.x = x + B.x;
	result.y = y + B.y;
	result.z = z + B.z;
	return result;
}*/
/*
vectorzz operator*(double multi, const vectorzz & B)
{
	vectorzz result = vectorzz(0, 0, 0);
	result.x = multi * B.x;
	result.y = multi * B.y;
	result.z = multi * B.z;
	return result;
}*/
vectorzz operator*(const vectorzz & B, double multi)
{
	vectorzz result = vectorzz(0, 0, 0);
	result.x = multi * B.x;
	result.y = multi * B.y;
	result.z = multi * B.z;
	return result;
}
