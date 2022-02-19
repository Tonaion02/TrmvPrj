#pragma once





enum PhaseType
{
	NonePhaseType = -1,
	Exploring,
	Battle,
	Dialoging
};





enum StatePhase
{
	NoneStatePhase = -1,
	On,
	Off,
	Paused
};





struct Phase
{
	StatePhase statePhase;
	PhaseType phaseType;
};