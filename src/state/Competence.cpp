#include "Competence.hpp"

using namespace state;

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

Competence::Competence()
{
	type = Attack;
	damage = 0;
	target = 0;
	range = 0;
	interest = 0;
	cooldown = 0;
	maxCooldown = 0;
}
