#pragma once
#include "../Enum.h"

class Movement
{
public:
	Movement(int x,int y,AnimationType type);
	~Movement();
	const int getX();
	const int getY();
	const AnimationType getDir();
private :
	int x;
	int y;
	AnimationType type;
};

