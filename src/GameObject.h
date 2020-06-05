#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "SimpleImage.h"

class GameEngine;


class GameObject :
	public DisplayableObject
{
public:
	GameObject(GameEngine* pGameEngine, int xStart, int yStart);

	~GameObject();

	void constructMainImageURL();

	virtual int loadImage();

	int getCurrentScreenX() { return m_iCurrentScreenX; }
	int getCurrentScreenY() { return m_iCurrentScreenY; }

	void setCurrentScreenX(int newX) { m_iCurrentScreenX = newX; }
	void setCurrentScreenY(int newY) { m_iCurrentScreenY = newY; }

public:
	GameEngine* pGameEngine;
	std::string typeName;

	std::string mainImageURL;

	// Main image, the objects may have other acting states and corresponding images
	SimpleImage mainImage;

	// Actual size
	int actual_width;
	int actual_height;
};

