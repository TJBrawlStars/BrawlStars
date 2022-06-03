#include "FriendLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/Setting.h"
#include"Tool/Tools.h"
//#include "LoadingScene.h"
//#include "MainScene.h"
//#include"Tool/SceneManager.h"
#pragma execution_character_set("utf-8")  

bool FriendLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FriendLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景
	_bg = Tools::SetBg(this);

	//返回按钮
	_back = Tools::ButtonCreate(Vec2(100, kVisibleSize.height - 100), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Tools::SwitchScene(this, Tools::SwitchSceneType::Up);
			}
		});

	//添加好友
	_addFriend = Tools::ButtonCreate("添加好友", Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.2f), this);
	_addFriend->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				//用文本框输入叭_text
			}
		});

	//这边应该有从网上读取好友数据，然后做成列表，emmm然后可以支持查看好友一些数据和私聊？

	return true;
}
