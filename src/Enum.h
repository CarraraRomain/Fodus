#pragma once

enum CommandType {
	Abstract,
	EndTurn,
	Debug,
	Move,
	Dead,
	Skill,
	Status,
	Damage,
	Restore,
	Poison,
	Spawn,
	Load,
	Mode,
	Exit
};

enum SkillType {
	Attack,
	Fireball,
	Rejuvenate,
	ZombieSpawn,
	Viper
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
