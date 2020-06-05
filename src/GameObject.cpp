#include "GameObject.h"
#include "DisplayableObject.h"
#include "GameEngine.h"

GameObject::GameObject(GameEngine* pGameEngine, int xStart, int yStart)
	: DisplayableObject(xStart, yStart, pGameEngine, 100, 100, true)
	, pGameEngine(pGameEngine)
{
	mainImageURL = "images/" + typeName + "_main.png";
	std::cout << "Creating GameObject..." << std::endl;
	setVisible(true);
}

GameObject::~GameObject()
{
}


void GameObject::constructMainImageURL()
{
	this->mainImageURL = "images/" + typeName + "_main.png";
}

int GameObject::loadImage()
{
	constructMainImageURL();
	if (!mainImageURL.empty())
	{
		std::cout << "Loading the image..." << std::endl;
		std::cout << "Image URL: " << mainImageURL << std::endl;
		mainImage = getEngine()->loadImage(mainImageURL, false);
		m_iDrawWidth = actual_width;
		m_iDrawHeight = actual_height;
		mainImage = mainImage.resizeTo(m_iDrawWidth, m_iDrawHeight);
		return 1;
	}
	else
	{
		return 0;
	}
}



