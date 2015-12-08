#pragma once

#include <string>
#include "../global.hpp"

class Competence
{
public:
	SkillType type;
	int damage;
	int interest;
	int target; // 0 -> empty tile    1 -> same side    2 -> other side
	int range;
	int cooldown;
	int maxCooldown;
	Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown);
	Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown, int newActualCooldown);
	~Competence();

	void used();
};