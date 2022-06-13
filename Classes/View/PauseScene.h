#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 游戏暂停与恢复界面
*/
class PauseScene :public cocos2d::Scene
{
public:

	CREATE_FUNC(PauseScene);

private:

	virtual bool init();

	PauseScene() : kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _readme(NULL), _resume(NULL) {};

	///**
	//* @brief 点击屏幕即消失
	//*/
	//virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	/*static void Capture(cocos2d::Scene* scene);

	static void AfterCapture(bool succeed, const std::string& outputFile);*/

private:

	const cocos2d::Size kVisibleSize;

	//设置暂停背景
	cocos2d::Sprite* _bg;

	//提醒已暂停，点击屏幕继续
	cocos2d::Label* _readme;

	//恢复按钮
	cocos2d::ui::Button* _resume;

	/*static cocos2d::Scene* _scene;

	static std::string _outputfile;*/

};


