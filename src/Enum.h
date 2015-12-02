#pragma once

enum CommandType {
	Abstract,
	EndTurn,
	Debug,
	Move,
	Attack,
	Dead,
	Skill,
	Status,
	Damage,
	Restore,
	Spawn,
	Load,
	Mode,
	Exit
};

enum SkillType {
	Fireball,
	Rejuvenate,
	ZombieSpawn
};

enum AiBehavior {
	Aggression,
	Fear
};
	
enum AnimationType
{
	MoveForward,
	MoveBackward,
	MoveRight,
	MoveLeft
};

enum ElementType
{
	Mobile,
	Fixed
};

enum ObsType
{
	ObsEngine,
	ObsState,
	ObsNetwork,
	ObsAnimation,
	ObsHUD
};

enum Classe {
	Principal,
	Zombie,
	Monstre,
	Guerrier,
	Mage,
	Sol
};
