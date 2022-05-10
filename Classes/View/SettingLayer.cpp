#include "SettingLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/Setting.h"
#include"Tool/Tools.h"

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
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType)
		{
			auto distory = RemoveSelf::create();
			auto move = MoveTo::create(0.5f, Vec2(0, kVisibleSize.height));
			this->runAction(Sequence::createWithTwoActions(move, distory));
           //做出划上划下的效果
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
			//滚动事件
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				const int percent = dynamic_cast<Slider*>(ref)->getPercent();
				Setting::getInstance()->SoundPercentSet(percent);
			}
		});

	_soundmenu = Tools::MenuCreate(Vec2(-75, 15), "ui/sound.png", "ui/sound_close.png"
		, CC_CALLBACK_1(SettingLayer::SoundmenuCloseCallback, this), _soundbar);
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
		if (item->getSelectedIndex() == 0)
			Setting::getInstance()->SoundSet(false);
		else
			Setting::getInstance()->SoundSet(true);
	}
}
