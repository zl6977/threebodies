#include "CalcClass.h"
/*
CalcClass::CalcClass()
{
}


CalcClass::~CalcClass()
{
}
*/
vectorzz CalcClass::calcGravity(const DynamicStatus &A, const DynamicStatus &B)
{
	vectorzz gravity = vectorzz(0, 0, 0);
	vectorzz distance = vectorzz(0, 0, 0);
	distance = B.postion - A.postion;
	double distanceMod = distance.modulus();
	double gravConst = 6.67e-11;
	double tmp1, tmp2, tmp3, tmp4;
	tmp1 = tmp2 = tmp3 = tmp4 = 0;
	tmp1 = gravConst * A.mass;
	tmp2 = tmp1 * B.mass;
	tmp3 = tmp2 / pow(distanceMod, 3);
	gravity = gravConst * A.mass*B.mass / distanceMod * distance / distanceMod / distanceMod;
	return gravity;
}

vectorzz CalcClass::sumForce(const DynamicStatus & A, const DynamicStatus & B, const DynamicStatus & C)
{
	vectorzz gravity1, gravity2;
	gravity1 = calcGravity(A, B);
	gravity2 = calcGravity(A, C);
	return gravity1 + gravity2;
}

void CalcClass::update_Ftoa(const vectorzz &force, DynamicStatus & A)
{
	A.acceleration = force / A.mass;
}

void CalcClass::update_atov(DynamicStatus & A, double deltaT)
{
	A.velocity = A.velocity + A.acceleration * deltaT;
}

void CalcClass::update_vtop(DynamicStatus & A, double deltaT)
{
	A.postion = A.postion + A.velocity * deltaT;
}

double CalcClass::minzz(const double a, const double b)
{
	if (a <= b)
		return a;
	else
		return b;
}

double CalcClass::minzz(const double a, const double b, const double c)
{
	return minzz(minzz(a, b), c);
}

void CalcClass::RK4zz(DynamicStatus & A, DynamicStatus & B, DynamicStatus & C, double h)
{
	vectorzz K1a[3], K2a[3], K3a[3], K4a[3];
	vectorzz K1v[3], K2v[3], K3v[3], K4v[3];
	DynamicStatus A_temp = A, B_temp = B, C_temp = C;
	CalcClass::update_Ftoa(CalcClass::sumForce(A_temp, B_temp, C_temp), A_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(B_temp, A_temp, C_temp), B_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(C_temp, B_temp, A_temp), C_temp);
	K1a[0] = A_temp.acceleration;
	K1a[1] = B_temp.acceleration;
	K1a[2] = C_temp.acceleration;
	K1v[0] = A_temp.velocity;
	K1v[1] = B_temp.velocity;
	K1v[2] = C_temp.velocity;
	//K2 below
	A_temp.postion = A_temp.postion + (A_temp.velocity + K1v[0]) * h / 2;
	B_temp.postion = B_temp.postion + (B_temp.velocity + K1v[1]) * h / 2;
	C_temp.postion = C_temp.postion + (C_temp.velocity + K1v[2]) * h / 2;
	CalcClass::update_Ftoa(CalcClass::sumForce(A_temp, B_temp, C_temp), A_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(B_temp, A_temp, C_temp), B_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(C_temp, B_temp, A_temp), C_temp);
	K2a[0] = A_temp.acceleration;
	K2a[1] = B_temp.acceleration;
	K2a[2] = C_temp.acceleration;
	K2v[0] = A_temp.velocity + h / 2 * K2a[0];
	K2v[1] = B_temp.velocity + h / 2 * K2a[1];
	K2v[2] = C_temp.velocity + h / 2 * K2a[2];
	//K3 below
	A_temp.postion = A_temp.postion + K2v[0] * h / 2;
	B_temp.postion = B_temp.postion + K2v[1] * h / 2;
	C_temp.postion = C_temp.postion + K2v[2] * h / 2;
	CalcClass::update_Ftoa(CalcClass::sumForce(A_temp, B_temp, C_temp), A_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(B_temp, A_temp, C_temp), B_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(C_temp, B_temp, A_temp), C_temp);
	K3a[0] = A_temp.acceleration;
	K3a[1] = B_temp.acceleration;
	K3a[2] = C_temp.acceleration;
	K3v[0] = A_temp.velocity + h / 2 * K3a[0];
	K3v[1] = B_temp.velocity + h / 2 * K3a[1];
	K3v[2] = C_temp.velocity + h / 2 * K3a[2];
	//K4 below
	A_temp.postion = A_temp.postion + K3v[0] * h;
	B_temp.postion = B_temp.postion + K3v[1] * h;
	C_temp.postion = C_temp.postion + K3v[2] * h;
	CalcClass::update_Ftoa(CalcClass::sumForce(A_temp, B_temp, C_temp), A_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(B_temp, A_temp, C_temp), B_temp);
	CalcClass::update_Ftoa(CalcClass::sumForce(C_temp, B_temp, A_temp), C_temp);
	K4a[0] = A_temp.acceleration;
	K4a[1] = B_temp.acceleration;
	K4a[2] = C_temp.acceleration;
	K4v[0] = A_temp.velocity + h / 2 * K4a[0];
	K4v[1] = B_temp.velocity + h / 2 * K4a[0];
	K4v[2] = C_temp.velocity + h / 2 * K4a[0];
	//update position acceleration,velocity
	A.postion = A.postion + (K1v[0] + 2 * K2v[0] + 2 * K3v[0] + K4v[0]) * h / 6;
	B.postion = B.postion + (K1v[1] + 2 * K2v[1] + 2 * K3v[1] + K4v[1]) * h / 6;
	C.postion = C.postion + (K1v[2] + 2 * K2v[2] + 2 * K3v[2] + K4v[2]) * h / 6;
	CalcClass::update_Ftoa(CalcClass::sumForce(A, B, C), A);
	CalcClass::update_Ftoa(CalcClass::sumForce(B, A, C), B);
	CalcClass::update_Ftoa(CalcClass::sumForce(C, B, A), C);
	A.velocity = A.velocity + (K1a[0] + 2 * K2a[0] + 2 * K3a[0] + K4a[0]) / 6;
	B.velocity = B.velocity + (K1a[1] + 2 * K2a[1] + 2 * K3a[1] + K4a[1]) / 6;
	C.velocity = C.velocity + (K1a[2] + 2 * K2a[2] + 2 * K3a[2] + K4a[2]) / 6;
}
/*
vectorzz CalcClass::RK4_K1(const DynamicStatus &A, double h)
{
	vectorzz K1;
	K1 = A.velocity + A.acceleration*h;
}
vectorzz CalcClass::RK4_K2(const DynamicStatus &A, double h)
{
	vectorzz K2;
	K2 = A.velocity + A.acceleration*h;
}
vectorzz CalcClass::RK4_K3(const DynamicStatus &A, double h)
{
	vectorzz K3;
	K3 = A.velocity + A.acceleration*h;
}
vectorzz CalcClass::RK4_K4(const DynamicStatus &A, double h)
{
	vectorzz K4;
	K4 = A.velocity + A.acceleration*h;
}
*/