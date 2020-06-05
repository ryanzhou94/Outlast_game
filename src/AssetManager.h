#pragma once
#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "header.h"
#include "cstdlib"
#include "SDL_mixer.h"
#include "SDL_filesystem.h"
#include <map>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2_image.lib")
#pragma comment(lib,"SDL2_mixer.lib")
#pragma comment(lib,"SDL2_ttf.lib")
#pragma comment(lib,"SDL2main.lib")
class AssetManager
{
private:
	static AssetManager* sInstance;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;

	AssetManager();
	~AssetManager();

public:
	static AssetManager* Instance();
	static void Release();

	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);
};

#endif // !1



