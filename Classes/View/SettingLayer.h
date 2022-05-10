#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 设置场景
*/
class SettingLayer :public cocos2d::Layer
{
public:

	CREATE_FUNC(SettingLayer);

private:

	virtual bool init();

	/**
	* @brief 菜单的设置(集成)
	*/
	void Set();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	SettingLayer() :_bg(NULL), _soundmenu(NULL), _soundbar(NULL), _back(NULL)
		, kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize()) {};

	/**
	* @brief 静音菜单的回调函数
	*/
	void SoundmenuCloseCallback(cocos2d::Ref* pSender);

private:

	const cocos2d::Size kVisibleSize;

	//设置画面背景
	cocos2d::ui::Scale9Sprite* _bg;

	//设置菜单
	cocos2d::Menu* _soundmenu;

	//声音控制滑条
	cocos2d::ui::Slider* _soundbar;

	//返回按钮
	cocos2d::ui::Button* _back;

};


