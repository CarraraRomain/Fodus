#pragma once
#include "../Enum.h"

class Movement
{
public:
	Movement(int x,int y,AnimationType type);
	~Movement();

private :
	int x;
	int y;
	AnimationType type;
};

