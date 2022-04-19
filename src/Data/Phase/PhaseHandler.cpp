#include "Phase.h"

#include "PhaseHandler.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class PhaseHandler
//-----------------------------------------------------------------------------------------------------------------------------------------
void PhaseHandler::addPhase(int typePhase, int statePhase=-1, int index=0)
{
	phaseStack[index] = new Phase;
	phaseStack[index]->phaseType = (PhaseType)typePhase;
	phaseStack[index]->statePhase = (StatePhase)statePhase;
}



void PhaseHandler::addPhaseBack(int typePhase, int statePhase)
{
	phaseStack.push_back(new Phase);
	phaseStack[phaseStack.size() - 1]->phaseType = (PhaseType)typePhase;
	phaseStack[phaseStack.size() - 1]->statePhase = (StatePhase)statePhase;
}



void PhaseHandler::setStatePhase(int typePhase, int statePhase)
{
	for (int iter = 0; iter < phaseStack.size(); iter++)
	{
		if (phaseStack[iter]->phaseType == typePhase)
		{
			phaseStack[iter]->statePhase = (StatePhase)statePhase;
			return;
		}
	}

	//CALL ASSERT IF WE ARRIVE TO THIS POINT
}



void PhaseHandler::removePhase(int typePhase)
{
	for (int iter = 0; iter < phaseStack.size(); iter++)
	{
		if (phaseStack[iter]->phaseType == typePhase)
		{
			delete phaseStack[iter];
			phaseStack.erase(phaseStack.begin() + iter);
		}
	}
}



std::size_t PhaseHandler::isTherePhase(int typePhase)
{
	for (std::size_t iter = 0; iter < phaseStack.size(); iter++)
	{
		if (phaseStack[iter]->phaseType == typePhase)
		{
			return iter;
		}
	}

	return phaseStack.size();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class PhaseHandler
//-----------------------------------------------------------------------------------------------------------------------------------------