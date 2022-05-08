#pragma once

//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
USING_NS_CC;
#include"ui/CocosGUI.h"
using namespace ui;
#include "Tool/SceneManager.h"

/**
* @brief 房间场景
*/
class RoomLayer :public Layer
{
public:

	CREATE_FUNC(RoomLayer);

private:

	virtual bool init();

private:

	const Vec2 kVisibleSize = Director::getInstance()->getVisibleSize();

	//登录画面背景
	Sprite* _bg = NULL;

	//选择hero按钮
	Button* _choose_hero = NULL;

	//开始对战按钮
	Button* _start;

};

