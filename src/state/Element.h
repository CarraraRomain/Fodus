#include <string>

class Element
{
public:
	void setX(int newX);
	int getX();

	void setY(int newY);
	int getY();

	void setD(int newD);
	int getD();

	void setKey(std::string key);
	std::string getKey();

private:
	std::string m_key;
	int m_x;
	int m_y;
	int m_d;
};