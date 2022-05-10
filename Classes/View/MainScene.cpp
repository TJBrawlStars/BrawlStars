#include "MainScene.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "LoadingScene.h"
#include "RoomLayer.h"
#include "SettingLayer.h"
#include "Tool/Setting.h"
#include "Tool/SceneManager.h"
#include "Tool/Tools.h"
#pragma execution_character_set("utf-8")  

bool MainScene::init()
{
	if (!Scene::init())
		return false;

	//设置loading界面
	if (SceneManager::getInstance()->isFirst())
	{
		//初始化Tools
		Tools::set();

		_loading = LoadingScene::create();
		assert(_loading != NULL);
		this->addChild(_loading, 100);
	}

	//设置背景
	_bg = Tools::SetBg("ui/MainBg.png", this);

	//各种按钮的实现
	_menu_button = Tools::ButtonCreate(Vec2(275, kVisibleSize.height - 40), "ui/menu.png", this);
	_menu_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				_set = SettingLayer::create();
				assert(_set);
				this->addChild(_set);
				Tools::SwitchScene(_set, Tools::SwitchSceneType::Down);
			}
		});

	_info_button = Tools::ButtonCreate(Vec2(77, kVisibleSize.height - 40), "ui/info.png", this);
	_info_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				//弹出个人信息显示层
			}
		});

	_play_button = Tools::ButtonCreate("对   战", Vec2(kVisibleSize.width - 200, 75), this);
	_play_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				_room = RoomLayer::create();
				assert(_room);
				this->addChild(_room);
				Tools::SwitchScene(_room, Tools::SwitchSceneType::Down);
			}
		});

	_back = Tools::ButtonCreate(Vec2(175, kVisibleSize.height - 40), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			//不这样的话点击和结束点击都会创建一个层，坑死我了
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->StopSound();
				_loading = LoadingScene::create();
				assert(_loading != NULL);
				this->addChild(_loading, 100);
				Tools::SwitchScene(_loading, Tools::SwitchSceneType::FadeIn);
			}
		});

	////主界面显示的人物
	//_figure = Sprite::create();
	//assert(_figure != NULL);
	//_figure->setPosition(kVisibleSize / 2);
	//this->addChild(_figure);

	return true;
}

//弃用

//Button* MainScene::ButtonCreate(const Vec2&& position, const std::string&& pic_name)
//{
//	auto button = Button::create("ui/button.png");
//	assert(button != NULL);
//
//	button->setScale9Enabled(true);
//	button->setCapInsets(Rect(5, 5, 15, 15));
//	button->setPosition(position);
//
//	auto sprite = Sprite::create(pic_name);
//	assert(sprite != NULL);
//
//	button->addChild(sprite);
//	button->setContentSize(Size(sprite->getContentSize().width + 50, sprite->getContentSize().height + 25));
//	sprite->setPosition(button->getContentSize() / 2);
//	this->addChild(button);
//	return button;
//}

//弃用

//Button* MainScene::ButtonCreate(const std::string&& words, const Vec2&& position)
//{
//	auto button = Button::create("ui/button_y.png");
//	assert(button != NULL);
//
//	button->setScale9Enabled(true);
//	button->setCapInsets(Rect(5, 5, 15, 15));
//	button->setPosition(position);
//
//	auto label = Label::createWithSystemFont(words, "微软雅黑", 50);
//	assert(label != NULL);
//	button->setTitleLabel(label);
//	button->setContentSize(Size(label->getContentSize().width + 125, label->getContentSize().height + 50));
//	this->addChild(button);
//	return button;
//}