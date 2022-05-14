#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 初始的登录场景,实际上继承自Layer然后贴在main场景上
*/
class LoadingScene :public cocos2d::Layer
{
public:

	CREATE_FUNC(LoadingScene);

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

private:

	virtual bool init();

	/**
	* @brief 设置登陆后的界面
	*/
	void LoadGame();

	LoadingScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _login_button(NULL), _start_button(NULL), _exit_button(NULL) {};

private:

	const cocos2d::Size kVisibleSize;

	//登录画面背景
	cocos2d::Sprite* _bg;

	//登录按钮
	cocos2d::ui::Button* _login_button;

	//开始游戏按钮
	cocos2d::ui::Button* _start_button;

	//退出按钮
	cocos2d::ui::Button* _exit_button;

};

