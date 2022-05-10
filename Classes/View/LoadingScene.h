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

	//弃用

	//**
	//* @brief 设置按钮并add进场景
	//* @param (Vec2&& pos)位置
	//* @param ( std::string title)按钮标题
	//* @param (std::string pic)图片路径
	//*/
	//cocos2d::ui::Button* SetButton(const cocos2d::Vec2&& pos, const std::string&& title, const std::string&& pic1, const std::string&& pic2);

	LoadingScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _login_button(NULL), _exit_button(NULL) {};

private:

	const cocos2d::Size kVisibleSize;

	//登录画面背景
	cocos2d::Sprite* _bg;

	//登录按钮
	cocos2d::ui::Button* _login_button;

	//退出按钮
	cocos2d::ui::Button* _exit_button;

};

