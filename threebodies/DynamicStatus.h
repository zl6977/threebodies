#pragma once
#include "vectorzz.h"
class DynamicStatus
{
public:
	DynamicStatus();
	~DynamicStatus();
//	DynamicStatus(char* new_name, double new_mass,vectorzz new_postion=vectorzz(0,0,0));
	DynamicStatus(char* new_name, double new_mass, 
		vectorzz new_postion = vectorzz(0, 0, 0), 
		vectorzz new_velocity = vectorzz(0, 0, 0));
	char* name;
	double mass;
	vectorzz postion;
	vectorzz velocity;
	vectorzz acceleration;
};

