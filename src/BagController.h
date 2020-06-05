#pragma once
#include "header.h"
#include "BagTileManager.h"
#include "AudioManager.h"

class PlayerObject;

class BagController
{
public:
	BagController(PlayerObject* pPlayerObject, std::string theBag);
	~BagController();

	void useProps();

	bool addProps(int propsValue);
	bool removeProps(int propsValue);
	bool removePropsIndex(int index);
	int isBagFull();
	void initializeBag(std::string theBag);
	void printBag();
	void getBagArray(char* bagArrary);
	bool consumeProps(int propsValue);
	bool consumeKey();
	bool consumeHP();
	bool consumeMP();

public:
	PlayerObject* pPlayerObject;
	BagTileManager* pBagTileManager;
	std::vector<int> bag;
	// 1. key
	// 2. hp
	// 3. mp
};

