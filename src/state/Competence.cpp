#include "Competence.hpp"

Competence::Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown)
{
	type = newType;
	damage = newDamage;
	target = newTarget;
	range = newRange;
	interest = newInterest;
	maxCooldown = newCooldown;
	cooldown = 0;
}

Competence::Competence(SkillType newType, int newDamage, int newTarget, int newInterest, int newRange, int newCooldown, int newActualCooldown)
{
	type = newType;
	damage = newDamage;
	target = newTarget;
	range = newRange;
	interest = newInterest;
	cooldown = newActualCooldown;
	maxCooldown = newCooldown;
}

Competence::~Competence()
{
}

void Competence::used()
{
	cooldown = maxCooldown;
}
