#include "MenuLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include"Tool/Tools.h"
#include"MainScene.h"
#include"SettingLayer.h"
#include"Tool/Setting.h"
#include"Tool/SceneManager.h"

bool MenuLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MenuLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景设置（侧边栏）
	_bg = Scale9Sprite::create("ui/button.png");
	assert(_bg);
	this->addChild(_bg);

	_bg->setCapInsets(Rect(5, 5, 15, 15));
	_bg->setContentSize(Size(100, 720));
	_bg->setPosition(Vec2(kVisibleSize.width - _bg->getContentSize().width / 2, kVisibleSize.height / 2));

	//在侧边栏上设置按钮
	Set();
	


	return true;
}

void MenuLayer::Set()
{
	auto posX = _bg->getPosition().x;
	auto posY = _bg->getContentSize().height;
		
	//设置
	_set = Tools::ButtonCreateN(Vec2(posX, posY * 0.9f), "ui/set.png", this);
	_set->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				auto main = MainScene::GetMainScene();
				auto set = SettingLayer::create();
				assert(set);
				main->addChild(set);
				Tools::SwitchScene(set, Tools::SwitchSceneType::Down);
			}
		});

	//排行榜
	_ranking= Tools::ButtonCreateN(Vec2(posX, posY * 0.8f), "ui/rank.png", this);
	_ranking->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				/*auto main = MainScene::GetMainScene();
				auto set = SettingLayer::create();
				assert(set);
				main->addChild(set);
				Tools::SwitchScene(set, Tools::SwitchSceneType::Down);*/
			}
		});

	//对战日志
	_log = Tools::ButtonCreateN(Vec2(posX, posY * 0.7f), "ui/log.png", this);
	_log->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
			}
		});

	//暂停
	_pause= Tools::ButtonCreateN(Vec2(posX, posY * 0.6f), "ui/pause.png", this);
	_pause->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Setting::getInstance()->SoundSet(false);
				SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_PauseScene, 1);
			}
		});

	
}

bool MenuLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*)
{
	if (touch->getLocation().x < _bg->getPosition().x)
		Tools::SwitchScene(this, Tools::SwitchSceneType::RightToLeft);
	return true;
}
