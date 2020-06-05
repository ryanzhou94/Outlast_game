#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

AssetManager* AssetManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AssetManager();
	}
	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("audio/" + filename);
	
	if (mMusic[fullpath] == nullptr)
	{
		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == NULL)
		{
			std::cout << "Failed to load audio" << std::endl;
		}
	}
	return mMusic[fullpath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
	std::string path = "audio/" + filename;

	if (mSFX[path] == nullptr)
	{
		mSFX[path] = Mix_LoadWAV(path.c_str());
		if (mSFX[path] == NULL)
		{
			std::cout << "Failed to load audio" << std::endl;
		}
	}
	return mSFX[path];
}
