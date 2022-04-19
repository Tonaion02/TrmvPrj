#pragma once

#include <vector>





struct Phase;

class PhaseHandler
{
public:
	void addPhase(int typePhase, int statePhase, int index);
	void addPhaseBack(int typePhase, int statePhase);
	void setStatePhase(int typePhase, int statePhase);
	void removePhase(int typePhase);
	std::size_t isTherePhase(int typePhase);

public:
	std::vector<Phase*> phaseStack;
};