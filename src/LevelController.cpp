#include "LevelController.h"

void LevelController::getLockedDoorPosition(int* XPosition, int* YPosition)
{
	switch (currentLevel)
	{
	case 1:
		// level1
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level1[i][j] == '4')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	case 2:
		// level2
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level2[i][j] == '4')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void LevelController::getFountainPosition(int* XPosition, int* YPosition)
{
	switch (currentLevel)
	{
	case 1:
		// level1
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level1[i][j] == '6')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	case 2:
		// level2
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level2[i][j] == '6')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void LevelController::getNoOpenedDoorPosition(int* XPosition, int* YPosition)
{
	switch (currentLevel)
	{
	case 1:
		// level1
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level1[i][j] == 'a')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	case 2:
		// level2
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (level2[i][j] == 'a')
				{
					*XPosition = j;
					*YPosition = i;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void LevelController::nextLevel()
{
	currentLevel++;
}
