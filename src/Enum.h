#pragma once

enum CommandType {
	Abstract,
	EndTurn,
	Debug,
	Move,
	Attack,
	Dead,
	Damage,
	FireBall,
	Load,
	Mode,
	Exit
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
