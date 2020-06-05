#include "BagTileManager.h"
#include "BagController.h"
#include "GameEngine.h"


BagTileManager::BagTileManager(BagController* pBagController)
	: TileManager(80, 80, 3, 2)
	, pBagController(pBagController)
	, space(ImageManager::get()->getImagebyURL("images/bagSpace.png", true, true))
	, key(ImageManager::get()->getImagebyURL("images/key.png", true, true))
	, hp(ImageManager::get()->getImagebyURL("images/hp.png", true, true))
	, mp(ImageManager::get()->getImagebyURL("images/mp.png", true, true))
{
	space = space.resizeTo(getTileWidth()- 4, getTileHeight()-4);
	key = key.resizeTo(50, 50);
	hp = hp.resizeTo(50, 50);
	mp = mp.resizeTo(50, 50);
	setTopLeftPositionOnScreen(1030, 550);
}

BagTileManager::~BagTileManager()
{
}

void BagTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	drawSpace(pEngine, pSurface, iMapX, iMapY);
	switch (getMapValue(iMapX, iMapY)) {
	case 0:
		drawSpace(pEngine, pSurface, iMapX, iMapY);
		break;
	case 1:
		drawKey(pEngine, pSurface, iMapX, iMapY);
		break;
	case 2:
		drawHP(pEngine, pSurface, iMapX, iMapY);
		break;
	case 3:
		drawMP(pEngine, pSurface, iMapX, iMapY);
		break;
	}
}


void BagTileManager::updateValues()
{
	for (int i = 0; i < getMapWidth(); i++)
	{
		for (int j = 0; j < getMapHeight(); j++)
		{
			int index = i + j * getMapWidth();
			setMapValue(i, j, pBagController->bag[index]);
		}
	}

}

void BagTileManager::setAndRedrawMapValueAtIndex(int index, int iValue, BaseEngine* pEngine, DrawingSurface* pSurface)
{
	int mapY = index / getMapWidth();
	int mapX = index - (mapY * getMapWidth());
	
	setAndRedrawMapValueAt(mapX, mapY, iValue, pEngine, pSurface);
}


void BagTileManager::drawSpace(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	space.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 2, m_iBaseScreenY + iMapY * getTileHeight() - 18, space.getWidth(), space.getHeight());
}

void BagTileManager::drawKey(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	key.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 15, m_iBaseScreenY + iMapY * getTileHeight() - 4, key.getWidth(), key.getHeight());
}

void BagTileManager::drawHP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	hp.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 15, m_iBaseScreenY + iMapY * getTileHeight() - 4, hp.getWidth(), hp.getHeight());
}

void BagTileManager::drawMP(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY) const
{
	mp.renderImageWithMask(pSurface, 0, 0, m_iBaseScreenX + iMapX * getTileWidth() + 15, m_iBaseScreenY + iMapY * getTileHeight() - 4, mp.getWidth(), mp.getHeight());
}
