#include "RoomLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include"Tool/Tools.h"
#include"Tool/Setting.h"
#pragma execution_character_set("utf-8")  

static constexpr int kEnemyTag = 0;
static constexpr int kOurTag = 1;

bool RoomLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RoomLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//层背景
	_bg = Tools::SetBg(this);

	//开始游戏按钮
	_start = Tools::ButtonCreate("开始对战", Vec2(kVisibleSize.width - 130, 75), this);
	_start->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_GameScene);
			}
		});

	//返回按钮
	_back = Tools::ButtonCreate(Vec2(77, kVisibleSize.height - 40), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Tools::SwitchScene(this, Tools::SwitchSceneType::Up);
			}
		});

	//6个房间成员框
	MemberCreate();

	//VS字样
	_vs = Tools::LabelCreateSystem(kVisibleSize / 2, "友谊战", "微软雅黑", 70, this);

	//自动补全机器人按钮
	_robots = Tools::ButtonCreate("补全机器人", Vec2(125, 100), this);
	_robots->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			//设置我方和敌方机器人个数
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				/*while (_enemy.setRobot(true));
				while (_our.setRobot(true));*/
				while (_member.setRobot(true));
				//遍历_figures实现翻转(使用基于范围的For循环)
				for (auto item : _figures)
				{
					if (item->getSelectedIndex() == 1);
					else if(item->getSelectedIndex() == 0)
						item->setSelectedIndex(1);
				}
			}
		});

	return true;
}

bool RoomLayer::onTouchBegan(cocos2d::Touch*, cocos2d::Event*)
{
	return true;
}

void RoomLayer::MemberCreate()
{
	//读取main场景的精灵
	//先把我方房主设置上
	PlusMemberCreate();
}

void RoomLayer::PlusMemberCreate()
{
	for (int i = 1; i <= 9; ++i)
	{
		auto box1 = MenuItemImage::create("ui/box.png", "ui/box.png");
		auto box2 = MenuItemImage::create("ui/box_robot.png", "ui/box_robot.png");
		assert(box1 != NULL);
		assert(box2 != NULL);
		//这边如果联机的话这个callback函数要改一下
		auto box0 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(RoomLayer::menuCloseCallback, this), box1, box2, NULL);
		_figures.pushBack(box0);
		auto box = Menu::create(box0, NULL);
		this->addChild(box);

		if (i <= 5)
		{
			//设置tag，方便之后根据tag控制哪个Menber成员的增减
			//box0->setTag(kEnemyTag);
			box->setPosition(Vec2(kVisibleSize.width / 2 + (i - 3) * 150, kVisibleSize.height / 2 + 200));
		}
		else
		{
			//设置tag，方便之后根据tag控制哪个Menber成员的增减
			//box0->setTag(kOurTag);
			box->setPosition(Vec2(kVisibleSize.width / 2 + (i - 7) * 150, kVisibleSize.height / 2 - 200));
		}
		box->setContentSize(Size(50, 125));
	    
	}
}

void RoomLayer::menuCloseCallback(Ref* pSender)
{
	//这边如果要有真人还需要来一个层选择，选择之后传给这里，然后来一个玩家的角色图像把原本机器人的图像盖住吧？（总之之后再说
	//或许可以加一个选择按钮的第二次点击是添加真人玩家？
	auto const item = dynamic_cast<MenuItemToggle*>(pSender);
	if (item)
	{
		if (item->getSelectedIndex()==1)
		{
			/*if (item->getTag() == kOurTag)
				_our.setRobot(true);
			else if (item->getTag() == kEnemyTag)
				_enemy.setRobot(true);*/
			_member.setRobot(true);
		}
		else
		{
			/*if (item->getTag() == kOurTag)
				_our.setRobot(false);
			else if (item->getTag() == kEnemyTag)
				_enemy.setRobot(false);*/
			_member.setRobot(false);
		}
	}
}


		
