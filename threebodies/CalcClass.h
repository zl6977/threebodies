#pragma once
#include "DynamicStatus.h"
#include "vectorzz.h"
#include <cmath>
class CalcClass
{
public:
	//CalcClass();
	//~CalcClass();
	static vectorzz calcGravity(const DynamicStatus &A, const DynamicStatus &B);
	static vectorzz sumForce(const DynamicStatus &A, const DynamicStatus &B, const DynamicStatus &C);
	static void update_Ftoa(const vectorzz &force, DynamicStatus &A);
	static void update_atov(DynamicStatus &A, double deltaT);
	static void update_vtop(DynamicStatus &A, double deltaT);
	static double minzz(const double a, const double b);
	static double minzz(const double a, const double b, const double c);
	static void RK4zz(DynamicStatus &A, DynamicStatus &B, DynamicStatus &C, double h);
	/*
	static vectorzz RK4_K1(const DynamicStatus &A, double h);
	static vectorzz RK4_K2(const DynamicStatus &A, double h);
	static vectorzz RK4_K3(const DynamicStatus &A, double h);
	static vectorzz RK4_K4(const DynamicStatus &A, double h);*/
};

