#pragma once
class vectorzz
{
public:
	vectorzz();
	vectorzz(double new_x, double new_y, double new_z);
	~vectorzz();
	double x, y, z;
	double modulus();
	/*
	vectorzz operator+(const vectorzz &B);
	vectorzz operator-(const vectorzz &B);
	vectorzz operator*(double multi);
	vectorzz operator/(double para);
	vectorzz &operator+=(const vectorzz &B);*/

	friend vectorzz operator+(const vectorzz &A, const vectorzz &B);
	friend vectorzz operator-(const vectorzz &A, const vectorzz &B);
	friend vectorzz operator*(double multi, const vectorzz &B);
	friend vectorzz operator/(const vectorzz &A, double para);
	//friend vectorzz &operator+=(const vectorzz &B);;
//	friend vectorzz operator*(double multi, const vectorzz &B);
	friend vectorzz operator*(const vectorzz & B, double multi);
};

