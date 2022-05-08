#pragma once

//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
USING_NS_CC;
#include"ui/CocosGUI.h"
using namespace ui;
#include "Tool/SceneManager.h"

/**
* @brief 初始的登录场景,实际上继承自Layer然后贴在main场景上
*/
class LoadingScene :public Layer
{
public:

	CREATE_FUNC(LoadingScene);

private:

	virtual bool init();

private:

	const Vec2 kVisibleSize = Director::getInstance()->getVisibleSize();

	//登录画面背景
	Sprite* _bg = NULL;

	//登录按钮
	Button* _login_button = NULL;

};

