#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 菜单侧边栏
*/
class MenuLayer :public cocos2d::Layer
{
public:

	CREATE_FUNC(MenuLayer);

private:

	virtual bool init();

	/**
	* @brief 菜单上面按钮的设置(集成)
	*/
	void Set();

	MenuLayer() :_bg(NULL), _set(NULL), _ranking(NULL), _log(NULL)
		, kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize()) {};

	/**
	* @brief 点击边界以外就消失
	*/
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

private:

	const cocos2d::Size kVisibleSize;

	//设置侧边栏
	cocos2d::ui::Scale9Sprite* _bg;

	//设置按钮
	cocos2d::ui::Button* _set;

	//排行榜按钮
	cocos2d::ui::Button* _ranking;

	//对战日志按钮
	cocos2d::ui::Button* _log;

	//暂停按钮
	cocos2d::ui::Button* _pause;

};

