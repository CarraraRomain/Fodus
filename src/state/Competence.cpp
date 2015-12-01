#include "Competence.hpp"

Competence::Competence(SkillType newType, int newDamage, int newTarget, int newRange)
{
	type = newType;
	damage = newDamage;
	target = newTarget;
	range = newRange;
	cooldown = 0;
}

Competence::~Competence()
{
}
