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
MSGPACK_ADD_ENUM(CommandType);
enum SkillType {
	Attack,
	Fireball,
	Rejuvenate,
	ZombieSpawn,
	Viper
};
MSGPACK_ADD_ENUM(SkillType);
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
MSGPACK_ADD_ENUM(AnimationType);

enum ElementType
{
	Mobile,
	Fixed
};
MSGPACK_ADD_ENUM(ElementType);
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
MSGPACK_ADD_ENUM(Classe);
