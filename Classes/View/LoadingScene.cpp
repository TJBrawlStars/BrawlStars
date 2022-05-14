#include "LoadingScene.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include "Tool/Setting.h"
#include "Tool/Tools.h"
#pragma execution_character_set("utf-8")  

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	//声音开始
	Setting::getInstance()->GoSound("audio/main.mp3");
	
	//设置吞噬点击事件(不知道为什么前两句加到封装里第二句等号会报错)
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoadingScene::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景的设置
	_bg = Tools::SetBg("ui/loadingBg.jpg", this);

	if (true)//如果没有登录信息的话,需要改这里
	{
		//登录按钮
		_login_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.3f)
			, "登      录", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
		//这边真要登录的话就新写一个函数叭
		_login_button->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
					auto distory = RemoveSelf::create();
					_login_button->runAction(distory);
					LoadGame();
				}
			});
	}

	return true;
}

void LoadingScene::LoadGame()
{
	/*-----------------------------------------------------------------------------------开始游戏按钮*/
	_start_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 150)
		, "开始游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_start_button->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Tools::SwitchScene(this, Tools::SwitchSceneType::FadeOut);
			}
		});

	/*-----------------------------------------------------------------------------------退出按钮*/
	_exit_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 250)
		, "结束游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_exit_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Director::getInstance()->end();
			}
		});

}

bool LoadingScene::onTouchBegan(Touch*, Event*)
{
	//这里要设置true这个loading层才会吞没点击事件，标记坑
	return true;
}

