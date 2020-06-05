#pragma once
#include "header.h"

class LevelController
{
public:
	LevelController() {}
	~LevelController() {}
	void getLockedDoorPosition(int* XPosition, int* YPosition);
	void getFountainPosition(int* XPosition, int* YPosition);
	void getNoOpenedDoorPosition(int* XPosition, int* YPosition);
	void nextLevel();

public:
	// 1. wall
	// 2. floor
	// 3. unlocked door
	// 4. locked door
	// 5. trap
	// 6. fountain
	// 7. bucket
	// 8, key
	// 9. HP
	// 0. MP
	// a. noOpenedDoor	10
	// b. bucketBroken	11

	int currentLevel = 1;

	const char level1[15][21] = {	"11411111111111111111",
									"12221222219221012221",
									"12221222212221212221",
									"12111222212221212221",
									"12222222012221222221",
									"12111111117771222221",
									"12222222212222222221",
									"12222222212111112221",
									"12222112212212212221",
									"12222112212212212221",
									"11117112511222212221",
									"12277112522222212221",
									"12211112522226212221",
									"18911112777722212221",
									"11111111111111111a11"	};

	const char level2[15][21] = {	"11111111111111111411",
									"19022211112219121221",
									"12222277772212721221",
									"12222211712212121521",
									"17777712212212121521",
									"12222217712212121521",
									"12222218712212121521",
									"15525511112212121221",
									"11525555552212121251",
									"11522555552212121251",
									"11112111552212121251",
									"12222552552212121251",
									"11212552552272127201",
									"12212556552212121551",
									"11a11111111111111111" };
};

