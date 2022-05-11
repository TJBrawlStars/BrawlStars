#pragma once
#include "Item.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Const/Const.h"

class DiamondBuff : public Item
{
public:
	CREATE_FUNC(DiamondBuff);

	/**
	* @初始化钻石
	*/
	bool virtual init() override;

	enum class Buff
	{
		health = 0,
		attack = 1
	};

	////暂时没用
	//void setDiamondPos(cocos2d::Vec2 position) { _DiamondPos = position; };

	//返回值是血量值和攻击值
	static int buffAttackOrHealth();
private:
	////暂时没用
	//cocos2d::Vec2 _DiamondPos;
};