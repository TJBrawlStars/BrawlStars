#include "RoomLayer.h"
USING_NS_CC;
using namespace ui;
#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include"Tool/Tools.h"
#include"Tool/Setting.h"
#include"Tool/Data.h"
#include"FigureLayer.h"
#include"Factory/HeroFactory.h"
#include"Const/Const.h"
#include<time.h>
#include <stdlib.h> 
#pragma execution_character_set("utf-8")  

//存放英雄信息传给游戏
extern std::vector<HeroData> herodataVec;

static constexpr int kEnemyTag = 0;
static constexpr int kOurTag = 1;
RoomLayer* RoomLayer::_that = NULL;

bool RoomLayer::init()
{
	if (!Layer::init())
		return false;

	_that = this;

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
				SetHero();
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

	//10个房间成员框
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
	//先把房主设置上
	_self = Tools::ButtonCreateN(Vec2(kVisibleSize.width / 2 + (-2) * 150, kVisibleSize.height / 2 - 200)
		, PlistData::getDataByType(PlistData::DataType::Figure), this);
	_self->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				auto changeFigure = FigureLayer::create();
				assert(changeFigure != 0);
				this->addChild(changeFigure);
				Tools::SwitchScene(changeFigure, Tools::SwitchSceneType::Down);
				_humandata.push_back(HumanData(PlistData::getDataByType(PlistData::DataType::Figure)));
			}
		});
	_humandata.push_back(HumanData("human"));

	PlusMemberCreate();
}

std::string RoomLayer::RandomHero(const std::vector<std::string>& heroID)
{
	int num = heroID.size();
	int a = rand() % num;
	return heroID.at(a);
}

void RoomLayer::PlusMemberCreate()
{
	for (int i = 1; i <= 9; ++i)
	{
		auto box1 = MenuItemImage::create("ui/box.png", "ui/box.png");
		auto box2 = MenuItemImage::create("ui/box_robot.png", "ui/box_robot.png");
		auto box3= MenuItemImage::create("ui/box_human.png", "ui/box_human.png");
		assert(box1 != NULL);
		assert(box2 != NULL);
		assert(box3 != NULL);
		//这边如果联机的话这个callback函数要改一下
		auto box0 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(RoomLayer::menuCloseCallback, this), box1, box2, box3, NULL);
		_figures.pushBack(box0);
		////设置tag，方便从vector里取
		//box0->setTag(i - 1);
		auto box = Menu::create(box0, NULL);
		this->addChild(box);

		if (i <= 5)
		{
			box->setPosition(Vec2(kVisibleSize.width / 2 + (i - 3) * 150, kVisibleSize.height / 2 + 200));
		}
		else
		{
			box->setPosition(Vec2(kVisibleSize.width / 2 + (i - 7) * 150, kVisibleSize.height / 2 - 200));
		}
		box->setContentSize(Size(50, 125));
	    
	}
}

void RoomLayer::SetButton()
{
	_current->removeChildByName("button1");
	_current->removeChildByName("button2");
	//遍历_figures实现恢复使用(使用基于范围的For循环)
	for (auto item : _figures)
		item->setEnabled(true);
}

void RoomLayer::SetHero()
{
	std::string name;
	//for (auto temp : _humandata)
	//{
	//	//这里之后用_humandata.get来获取角色英雄
	//	name = PlistData::getDataByType(;
	//	name += " false";
	//	herodataVec.push_back(HeroData(name, PlistData::getDataByType(PlistData::DataType::ID)));
	//}
	auto heroVec = HeroFactory::getInstance()->getClassIDVec();
	srand(time(NULL));
	for (int i = 0; i < _member.getRobot(); ++i)
	{
		//之后这边给机器人随机一个hero吧
		name = RandomHero(heroVec);
		name += " true";
		herodataVec.push_back(HeroData(name));
	}
}

void RoomLayer::menuCloseCallback(Ref* pSender)
{
	//这边如果要有真人还需要来一个层选择，选择之后传给这里，然后来一个玩家的角色图像把原本机器人的图像盖住吧？（总之之后再说
	//或许可以加一个选择按钮的第二次点击是添加真人玩家？
	auto const item = dynamic_cast<MenuItemToggle*>(pSender);
	if (item)
	{
		_current = item;
		if (item->getSelectedIndex()==1)
		{
			//遍历_figures实现其他菜单不能使用(使用基于范围的For循环)
			for (auto item : _figures)
				item->setEnabled(false);
			Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
			auto button1 = Tools::ButtonCreate("机器人", Vec2(_current->getContentSize().width / 2, _current->getContentSize().height/2 + 75), item);
			button1->setName("button1");
			button1->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
				{
					if (type == Widget::TouchEventType::ENDED)
					{
						Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
						_member.setRobot(true);
						_current->setName("robot");
						_current->setSelectedIndex(1);
						SetButton();
					}
				});
			//玩家这里以后做一个回调函数吧
			//
			//
			//
			//
			auto button2 = Tools::ButtonCreate("玩家", Vec2(_current->getContentSize().width / 2, _current->getContentSize().height/2 - 75), item);
			button2->setName("button2");
			button2->addTouchEventListener([&item, this](Ref*, Widget::TouchEventType type)
				{
					if (type == Widget::TouchEventType::ENDED)
					{
						Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
						/*_member.setHuman(true);
						_current->setName("human");*/
						_current->setSelectedIndex(0);
						SetButton();
					}
				});
		}
		else
		{
			item->setSelectedIndex(0);
			Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
			if (item->getName() == "robot")
				_member.setRobot(false);
			else if (item->getName() == "human")
				_member.setHuman(false);
		}
	}
}

void RoomLayer::setSelf(const std::string& filename)
{
	if (_that != NULL)
	{
		_that->scheduleOnce([filename](float dlt)
			{
				_that->_self->runAction(RemoveSelf::create());
				_that->_self = Tools::ButtonCreateN(Vec2(_that->kVisibleSize.width / 2 + (-2) * 150, _that->kVisibleSize.height / 2 - 200)
					, filename, _that);
				_that->_self->addTouchEventListener([](Ref*, Widget::TouchEventType type)
					{
						if (type == Widget::TouchEventType::ENDED)
						{
							Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
							auto changeFigure = FigureLayer::create();
							assert(changeFigure != 0);
							_that->addChild(changeFigure);
							Tools::SwitchScene(changeFigure, Tools::SwitchSceneType::Down);
						}
					});
			}, 0.5f, "delaytime");
	}
}

