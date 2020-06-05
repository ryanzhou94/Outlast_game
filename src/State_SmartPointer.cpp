#include "State_SmartPointer.h"
#include "GameEngine.h"

State_SmartPointer::State_SmartPointer(GameState* pGameState)
	: pState(pGameState)
	, pCount(new int)
{
	*pCount = 1;
}

State_SmartPointer::State_SmartPointer(State_SmartPointer& ssp)
	: pState(ssp.pState)
	, pCount(ssp.pCount)
{
	std::cout << "\tPointer incrementing ref count" << std::endl;
	(*pCount)++;
}

State_SmartPointer::~State_SmartPointer()
{
	release();
}

State_SmartPointer& State_SmartPointer::operator=(State_SmartPointer& ssp)
{
	release(); // drop any current content I have m_pData = refOther.m_pData;
	pCount = ssp.pCount;
	std::cout << "\tPointer incrementing ref count" << std::endl;
	(*pCount)++;
	return *this;
}

GameState& State_SmartPointer::operator*()
{
	return *pState;	// return the object
}

GameState* State_SmartPointer::operator->()
{
	return pState;	// return the pointer
}

GameState* State_SmartPointer::getRawPointer()
{
	return pState;
}

void State_SmartPointer::release()
{
	if (*pCount == 1) // If we are last pointer to data
	{
		std::cout << "\tPointer destroying object" << std::endl; if (pCount != nullptr)
		{
			delete pState; 
			delete pCount;
		}
	}
	else // Else there is at least one other pointer to data 
	{
		std::cout << "\tPointer decrementing ref count" << std::endl;
		(*pCount)--;
	}
	pState = nullptr;
	pCount = nullptr;
}

void State_SmartPointer::switchState(GameState* pGameState)
{
	release();
	this->pState = pGameState;
	pState->getPGameEngine()->lockAndSetupBackground();
	pState->getPGameEngine()->virtInitialiseObjects();
	this->pCount = new int(1);
}

void State_SmartPointer::pauseState(GameState* pPauseState)
{
	this->pState = pPauseState;
	pState->getPGameEngine()->pause();
	pState->getPGameEngine()->lockAndSetupBackground();
}

void State_SmartPointer::unPauseState(GameState* pGameState)
{
	this->pState = pGameState;
	pState->getPGameEngine()->unpause();
	pState->getPGameEngine()->setAllObjectsVisible(true);
	pState->getPGameEngine()->lockAndSetupBackground();
}
