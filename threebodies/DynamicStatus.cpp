#include "DynamicStatus.h"



DynamicStatus::DynamicStatus()
{
}


DynamicStatus::~DynamicStatus()
{
}
/*
DynamicStatus::DynamicStatus(char* new_name, double new_mass, vectorzz new_postion )
{
	name = new_name;
	mass = new_mass;
	postion = new_postion;
}*/

DynamicStatus::DynamicStatus(char * new_name, double new_mass, vectorzz new_postion, vectorzz new_velocity)
{
	name = new_name;
	mass = new_mass;
	postion = new_postion;
	velocity = new_velocity;
}
