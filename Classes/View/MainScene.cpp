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
#include "FigureLayer.h"
#include "InforLayer.h"
#include "MenuLayer.h"
#include "FriendLayer.h"
#include "Tool/Data.h"
#pragma execution_character_set("utf-8")  

MainScene* MainScene::_that = NULL;

void MainScene::SetInfo(const std::string& filename)
{
	_info_button->removeAllChildren();
	auto item = Sprite::create(filename);
	assert(item);
	_info_button->setName(filename);
	_info_button->addChild(item);
	item->setPosition(_info_button->getContentSize() / 2);
}

std::string MainScene::GetInfo()
{
	return _info_button->getName();
}

void MainScene::Load()
{
	//主界面显示的人物
	_figure = Tools::ButtonCreateN(kVisibleSize / 2, PlistData::getDataByType(PlistData::DataType::Figure), this);
	_figure->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				_changeFigure = FigureLayer::create();
				assert(_changeFigure != 0);
				this->addChild(_changeFigure, 100);
				Tools::SwitchScene(_changeFigure, Tools::SwitchSceneType::Down);
			}
		});

	//个人信息按钮
	_info_button = Tools::ButtonCreate(Vec2(77, kVisibleSize.height - 40), PlistData::getDataByType(PlistData::DataType::Profile), this);
	_info_button->setName("ui/info1.png");
	_info_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				_info = InforLayer::create();
				assert(_info);
				this->addChild(_info);
				Tools::SwitchScene(_info, Tools::SwitchSceneType::Down);
			}
		});
}

bool MainScene::init()
{
	if (!Scene::init())
		return false;

	_that = this;
	//初始化Tools
	Tools::set();

	//设置背景
	_bg = Tools::SetBg("ui/MainBg.png", this);

	//设置loading界面
	if (!Setting::getInstance()->isLogin())
	{
		_loading = LoadingScene::create();
		assert(_loading != NULL);
		this->addChild(_loading, 100);
	}
	else
		Load();

	//菜单按钮
	_menu_button = Tools::ButtonCreate(Vec2(275, kVisibleSize.height - 40), "ui/menu.png", this);
	_menu_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				_menu = MenuLayer::create();
				assert(_menu);
				this->addChild(_menu);
				Tools::SwitchScene(_menu, Tools::SwitchSceneType::LeftToRight);
			}
		});

	//开房间按钮
	_play_button = Tools::ButtonCreate("对   战", Vec2(kVisibleSize.width - 200, 75), this);
	_play_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				_room = RoomLayer::create();
				assert(_room);
				this->addChild(_room, 100);
				Tools::SwitchScene(_room, Tools::SwitchSceneType::Down);
			}
		});

	//返回按钮
	_back = Tools::ButtonCreate(Vec2(175, kVisibleSize.height - 40), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			//不这样的话点击和结束点击都会创建一个层，坑死我了
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Setting::getInstance()->StopSound();
				_loading = LoadingScene::create();
				assert(_loading != NULL);
				this->addChild(_loading, 100);
				Tools::SwitchScene(_loading, Tools::SwitchSceneType::FadeIn);
			}
		});

	//好友按钮
	_friends = Tools::ButtonCreate(Vec2(375, kVisibleSize.height - 40), "ui/friend.png", this);
	_friends->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				_friend = FriendLayer::create();
				assert(_friend);
				this->addChild(_friend);
				Tools::SwitchScene(_friend, Tools::SwitchSceneType::Down);
			}
		});

	//消息按钮
	_messages = Tools::ButtonCreate(Vec2(75, 40), "ui/message.png", this);
	_messages->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				//聊天系统，这边做一个聊天的侧边栏叭
			}
		});

	CCLOG("main finish");
	return true;
}

void MainScene::SetFigure(const std::string& filename)
{
	if (filename != _figure->getNormalFile().file)
	{
		this->scheduleOnce([this, filename](float dlt)
			{
				_figure = Tools::ButtonCreateN(kVisibleSize / 2, filename, this);
				_figure->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
					{
						if (type == Widget::TouchEventType::ENDED)
						{
							_changeFigure = FigureLayer::create();
							assert(_changeFigure != 0);
							this->addChild(_changeFigure);
							Tools::SwitchScene(_changeFigure, Tools::SwitchSceneType::Down);
						}
					});
			}, 0.5f, "delaytime");
	}
}

std::string MainScene::GetFigure() const
{
	return _figure->getNormalFile().file;
}
