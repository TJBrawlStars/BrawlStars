#pragma once
#include "Item.h"
#include "cocos2d.h"
#include "Const/Const.h"

/**
* @ author:张靖凯
* @ 实现宝箱类
*/
class TreasureBox : public Item
{
public:
	CREATE_FUNC(TreasureBox);

	bool virtual init() override;
	
	TreasureBox* createBox();

protected:
	Item* _BoxItem;
};
