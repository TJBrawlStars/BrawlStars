//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"

/**
* @class Diamond
* @brief a member of treasure box
*/
class Diamond :public cocos2d::Sprite
{
public:
	static Diamond* createDiamond();

private:
	Diamond() {}
	bool initWithFile(const std::string& filename);
	void initializeDiamondPhysics();
};