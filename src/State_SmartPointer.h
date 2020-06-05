#pragma once
#include "header.h"
#include "GameState.h"
#include "PauseState.h"

class GameEngine;

class State_SmartPointer
{
public:
	State_SmartPointer(GameState* pGameState);
	State_SmartPointer(State_SmartPointer& ssp);
	~State_SmartPointer();
	State_SmartPointer& operator = (State_SmartPointer& ssp);
	GameState& operator * ();
	GameState* operator -> ();
	GameState* getRawPointer();
	void release();
	void switchState(GameState* pGameState);
	void pauseState(GameState* pPauseState);
	void unPauseState(GameState* pGameState);

	
protected:
	GameState* pState;
	int* pCount;
};

