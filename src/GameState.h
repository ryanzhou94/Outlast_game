#pragma once
#include "header.h"

class GameEngine;

class GameState
{
public:
	GameState(GameEngine* pGameEngine);
	~GameState();
	virtual void virtSetupBackgroundBuffer() = 0;

	virtual void virtKeyDown(int iKeyCode) {}
	virtual void virtKeyUp(int iKeyCode) {}

	virtual void virtMouseDown(int iButton, int iX, int iY) {}
	virtual void virtMouseUp(int iButton, int iX, int iY) {}
	virtual void virtMouseMoved(int iX, int iY) {};
	virtual void virtBackgroundMouseDown(int iButton, int iRealX, int iRealY, int iVirtualX, int iVirtualY) {}
	virtual void virtMouseWheel(int x, int y, int which, int timestamp) {}

	//virtual int virtInitialise() { return 0; }
	virtual void virtRealMouseDown(int iButton, int iX, int iY) {}
	virtual void virtInitialiseObjects() {}
	virtual void virtCleanUp() {}
	virtual void virtPostDraw() {}

	virtual void virtDrawStringsUnderneath() {}
	virtual void virtDrawStringsOnTop() {}

	virtual void virtMouseDown(int X, int Y) {}

	GameEngine* getPGameEngine() { return this->pGameEngine; }

private:
	GameEngine* pGameEngine;
};

