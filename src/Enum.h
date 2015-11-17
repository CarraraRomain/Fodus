#pragma once

enum CommandType {
	Abstract,
	EndTurn,
	Debug,
	Move,
	Attack,
	Damage,
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
};