#include <iostream>

using namespace std;

class Elememt
{
private:
	int posX, posY, direction;

public:
	void setX(int x)
	{
		posX = x;
	}
	void getPosX(int &x)
	{
		x = posX;
	}

	void setY(int y)
	{
		posY = y;
	}
	void getPosY(int &y)
	{
		y = posY;
	}

	void setDirection(int d)
	{
		direction = d;
	}
	void getDirection(int &d)
	{
		d = direction;
	}
};