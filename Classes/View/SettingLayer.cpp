#include "SettingLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/Setting.h"
#include"Tool/Tools.h"
#include "LoadingScene.h"
#include "MainScene.h"
#include"Tool/SceneManager.h"
#include"Net/Client.h"
#pragma execution_character_set("utf-8")  

bool SettingLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SettingLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景
	_bg = Tools::SetBg(this);

	//设置菜单
	Set();

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

	return true;
}

void SettingLayer::Set()
{
	/*------------------------------------------------------------------------------------------声音部分*/
	_soundbar = Tools::SliderCreate(Vec2(kVisibleSize.width / 2.f, kVisibleSize.height * 0.8f)
		, "ui/bar.png", "ui/bartexture.png", "ui/slider.png", this);
	_soundbar->addEventListener([&](Ref* ref, Slider::EventType type)
		{
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				const int percent = dynamic_cast<Slider*>(ref)->getPercent();
				Setting::getInstance()->SoundPercentSet(percent);
			}
		});

	_soundmenu = Tools::MenuCreate(Vec2(-75, 15), "ui/sound.png", "ui/sound_close.png"
		, CC_CALLBACK_1(SettingLayer::SoundmenuCloseCallback, this), _soundbar);
	auto label1 = Tools::LabelCreateSystem(Vec2(_soundbar->getPosition().x, _soundbar->getPosition().y + 50)
		, "背景音", "微软雅黑", 30, this);
	label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	//如果已经设置成静音了就改变图像
	if (!Setting::getInstance()->isSound())
		dynamic_cast<MenuItemToggle*>(_soundmenu->getChildByTag(0))->setSelectedIndex(1);

	/*------------------------------------------------------------------------------------------音效部分*/
	_sound_effectBar = Tools::SliderCreate(Vec2(kVisibleSize.width / 2.f, kVisibleSize.height * 0.6f)
		, "ui/bar.png", "ui/bartexture.png", "ui/slider.png", this);
	_sound_effectBar->addEventListener([&](Ref* ref, Slider::EventType type)
		{
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				const int percent = dynamic_cast<Slider*>(ref)->getPercent();
				Setting::getInstance()->SoundEffectPercentSet(percent);
			}
		});

	_sound_effectMenu = Tools::MenuCreate(Vec2(-75, 15), "ui/sound.png", "ui/sound_close.png"
		, CC_CALLBACK_1(SettingLayer::SoundEffectmenuCloseCallback, this), _sound_effectBar);
	auto label2 = Tools::LabelCreateSystem(Vec2(_sound_effectBar->getPosition().x, _sound_effectBar->getPosition().y + 50)
		, "音效", "微软雅黑", 30, this);
	label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	if (!Setting::getInstance()->isSoundEffect())
		dynamic_cast<MenuItemToggle*>(_sound_effectMenu->getChildByTag(0))->setSelectedIndex(1);

	/*------------------------------------------------------------------------------------------网络部分*/
	auto client_menu1 = MenuItemImage::create("ui/net_client1.png", "ui/net_client1.png");
	auto client_menu2 = MenuItemImage::create("ui/net_client2.png", "ui/net_client2.png");
	assert(client_menu1 != NULL);
	assert(client_menu2 != NULL);

	_client_menu0 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuCloseCallback, this), client_menu1, client_menu2, NULL);
	auto client_menu = Menu::create(_client_menu0, NULL);
	client_menu->setPosition(Vec2(kVisibleSize.width / 2.f, kVisibleSize.height * 0.4f));
	if (Client::getInstance() != NULL)
		_client_menu0->setSelectedIndex(1);
	this->addChild(client_menu);

	/*------------------------------------------------------------------------------------------账号部分*/
	_exit = Tools::ButtonCreate("退出登录", Vec2(kVisibleSize.width / 2.f, kVisibleSize.height * 0.2f), this);
	_exit->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				//这边还要删掉本地账号信息
				Setting::getInstance()->StopSound();
				Setting::getInstance()->SetLogin(false);
				SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_MainScene);
				auto distory = RemoveSelf::create();
				this->runAction(distory);
			}
		});

}

void SettingLayer::menuCloseCallback(Ref* pSender)
{
	auto const item = dynamic_cast<MenuItemToggle*>(pSender);
	if (item)
	{
		Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
		if (item->getSelectedIndex() == 1)
		{
			_client_menu0->setSelectedIndex(0);
			auto text = Tools::TextCreate(Vec2(kVisibleSize.width / 2.f + 175, kVisibleSize.height * 0.4f), "输入服务器ip地址", 16, this);
			text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
			text->addEventListener(CC_CALLBACK_2(SettingLayer::TextFieldEvent, this));
		}
		else
		{
			Client::getInstance()->Close();
			CCLOG("Client close");
			Socket::close_Socket();
		}
	}
}

bool SettingLayer::onTouchBegan(cocos2d::Touch*, cocos2d::Event*)
{
	return true;
}

void SettingLayer::SoundmenuCloseCallback(cocos2d::Ref* pSender)
{
	const auto item = dynamic_cast<MenuItemToggle*>(pSender);
	if (item)
	{
		Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
		if (item->getSelectedIndex() == 1)
			Setting::getInstance()->SoundSet(false);
		else
			Setting::getInstance()->SoundSet(true);
	}
}

void SettingLayer::SoundEffectmenuCloseCallback(cocos2d::Ref* pSender)
{
	const auto item = dynamic_cast<MenuItemToggle*>(pSender);
	if (item)
	{
		Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
		if (item->getSelectedIndex() == 1)
			Setting::getInstance()->SoundEffectSet(false);
		else
			Setting::getInstance()->SoundEffectSet(true);
	}
}

void SettingLayer::TextFieldEvent(Ref* pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		dynamic_cast<TextField*>(pSender)->setString("|");
		break;
	}
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		auto item = dynamic_cast<TextField*>(pSender);
		auto ip = item->getString().substr(1);

		Socket::init_Socket();
		if (Client::getInstance(ip) != NULL)
		{
			_client_menu0->setSelectedIndex(1);
			Client::getInstance()->Start();
		}
		else
		{
			Client::getInstance()->Close();
			Socket::close_Socket();
			_client_menu0->setSelectedIndex(0);
		}

		auto distory = RemoveSelf::create();
		item->runAction(distory);
		break;
	}
	default:
		break;
	}
}

