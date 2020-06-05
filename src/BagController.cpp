#include "BagController.h"
#include "PlayerObject.h"

BagController::BagController(PlayerObject* pPlayerObject, std::string theBag)
	: pPlayerObject(pPlayerObject)
	, pBagTileManager(new BagTileManager(this))
{
	initializeBag(theBag);
	pBagTileManager->updateValues();
}

BagController::~BagController()
{
	delete pBagTileManager;
}

void BagController::useProps()
{
	if (pPlayerObject->getEngine()->isKeyPressed(SDLK_1))
	{
		removePropsIndex(0);
	}
	else if (pPlayerObject->getEngine()->isKeyPressed(SDLK_2))
	{
		removePropsIndex(1);
	}
	else if (pPlayerObject->getEngine()->isKeyPressed(SDLK_3))
	{
		removePropsIndex(2);
	}
	else if (pPlayerObject->getEngine()->isKeyPressed(SDLK_4))
	{
		removePropsIndex(3);
	}
	else if (pPlayerObject->getEngine()->isKeyPressed(SDLK_5))
	{
		removePropsIndex(4);
	}
	else if (pPlayerObject->getEngine()->isKeyPressed(SDLK_6))
	{
		removePropsIndex(5);
	}
}

bool BagController::addProps(int propsValue)
{
	bool isSuccessful = false;
	if (isBagFull() != -1)
	{
		for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
		{
			if (*iter == 0)
			{
				*iter = propsValue;
				isSuccessful = true;
				pBagTileManager->setAndRedrawMapValueAtIndex(std::distance(bag.begin(), iter), propsValue, pPlayerObject->getEngine(), pPlayerObject->getEngine()->getBackgroundSurface());
				break;
			}
		}
	}
	return isSuccessful;
}

bool BagController::removeProps(int propsValue)
{
	bool isSuccessful = false;
	if (propsValue != 0)
	{
		for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
		{
			if (*iter == propsValue)
			{
				if (consumeProps(*iter))
				{
					*iter = 0;
					isSuccessful = true;
					pBagTileManager->setAndRedrawMapValueAtIndex(std::distance(bag.begin(), iter), 0, pPlayerObject->getEngine(), pPlayerObject->getEngine()->getBackgroundSurface());
					break;
				}
			}
		}
	}
	return isSuccessful;
}

bool BagController::removePropsIndex(int index)	// from 0 to 5
{
	bool isSuccessful = false;
	if (index >= 0 && index <= 5)
	{
		for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
		{
			if (std::distance(bag.begin(), iter) == index)
			{
				if (consumeProps(*iter))
				{
					*iter = 0;
					isSuccessful = true;
					pBagTileManager->setAndRedrawMapValueAtIndex(index, 0, pPlayerObject->getEngine(), pPlayerObject->getEngine()->getBackgroundSurface());
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
	return isSuccessful;
}

int BagController::isBagFull()
{
	int emptySpace = -1;	// no empty space
	for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
	{
		if (*iter == 0)
		{
			emptySpace = std::distance(bag.begin(), iter);
			break;
		}
	}
	return emptySpace;
}

void BagController::initializeBag(std::string theBag)
{
	bag.resize(6);
	for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
	{
		*iter = theBag[std::distance(bag.begin(), iter)] - '0';
	}
	
}

void BagController::printBag()
{
	std::cout << "You had:";
	for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
	{
		if (*iter != 0)
		{
			switch (*iter)
			{
			case 1:
				std::cout << " Key";
				break;
			case 2:
				std::cout << " HP";
				break;
			case 3:
				std::cout << " MP";
				break;
			default:
				break;
			}
		}
	}
	std::cout << std::endl;
}

void BagController::getBagArray(char* bagArrary)
{
	for (std::vector<int>::iterator iter = bag.begin(); iter != bag.end(); iter++)
	{
		bagArrary[std::distance(bag.begin(), iter)] = *iter + '0';
	}
	bagArrary[6] = 0;
}

bool BagController::consumeProps(int propsValue)
{
	bool isSuccessful = false;
	switch (propsValue)
	{
	case 1:
		// use key
		if (consumeKey())
		{
			AudioManager::Instance()->PlaySFX("openDoor.wav");
			isSuccessful = true;
		}
		break;
	case 2:
		// use HP
		if (consumeHP())
		{
			AudioManager::Instance()->PlaySFX("drink.wav");
			isSuccessful = true;
		}
		break;
	case 3:
		// use MP
		if (consumeMP())
		{
			AudioManager::Instance()->PlaySFX("drink.wav");
			isSuccessful = true;
		}
		break;
	default:
		break;
	}
	return isSuccessful;
}

bool BagController::consumeKey()
{
	bool isSuccessful = false;
	if (pPlayerObject->pGameTileManager->isPlayerAroundDoor(pPlayerObject))
	{
		pPlayerObject->pGameTileManager->openLockedDoor(pPlayerObject, pPlayerObject->getEngine(), pPlayerObject->getEngine()->getBackgroundSurface());
		isSuccessful = true;
	}
	return isSuccessful;
}

bool BagController::consumeHP()
{
	bool isSuccessful = false;
	if (pPlayerObject->HP < pPlayerObject->maxHP)
	{
		if (pPlayerObject->HP + 25 >= pPlayerObject->maxHP)
		{
			pPlayerObject->HP = pPlayerObject->maxHP;
		}
		else
		{
			pPlayerObject->HP += 25;
		}
		isSuccessful = true;
	}
	return isSuccessful;
}

bool BagController::consumeMP()
{
	bool isSuccessful = false;
	if (pPlayerObject->MP < pPlayerObject->maxMP)
	{
		if (pPlayerObject->MP + 400 >= pPlayerObject->maxMP)
		{
			pPlayerObject->MP = pPlayerObject->maxMP;
		}
		else
		{
			pPlayerObject->MP += 400;
		}
		isSuccessful = true;
	}
	return isSuccessful;
}
