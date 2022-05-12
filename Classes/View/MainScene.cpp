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
#pragma execution_character_set("utf-8")  

MainScene* MainScene::_that = NULL;

bool MainScene::init()
{
	if (!Scene::init())
		return false;

	_that = this;

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

	//菜单按钮
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

	//个人信息按钮
	_info_button = Tools::ButtonCreate(Vec2(77, kVisibleSize.height - 40), "ui/info.png", this);
	_info_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				_info = InforLayer::create();
				assert(_info);
				this->addChild(_info);
				Tools::SwitchScene(_info, Tools::SwitchSceneType::Down);
			}
		});

	//开房间按钮
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

	//返回按钮
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

	//主界面显示的人物(默认第一个）
	_figure = Tools::ButtonCreateN(kVisibleSize / 2, "ui/figure1.jpg", this);
	_figure->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				_changeFigure = FigureLayer::create();
				assert(_changeFigure != 0);
				this->addChild(_changeFigure, 100);
				Tools::SwitchScene(_changeFigure, Tools::SwitchSceneType::Down);
			}
		});

	return true;
}

void MainScene::SetFigure(const std::string& filename)
{
	if (filename != _figure->getNormalFile().file)
	{
		this->scheduleOnce([this, &filename](float dlt)
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
