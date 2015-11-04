#include <string>

class LegacyElement
{
public:
	void setX(int newX);
	int getX();

	void setY(int newY);
	int getY();

	void setD(int newD);
	int getD();

	int getUid();

	void setKey(std::string key);
	std::string getKey();

	virtual bool isGround();
	virtual bool isPerso();
	virtual bool isAllie();
	virtual bool isNeutral();
	virtual bool isEnnemy();

private:
	std::string m_key;
	int m_x;
	int m_y;
	int m_d;
	int uid;
};