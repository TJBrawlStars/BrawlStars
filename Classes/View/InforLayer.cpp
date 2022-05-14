#include "InforLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/Setting.h"
#include"Tool/Tools.h"
#include "MainScene.h"
#pragma execution_character_set("utf-8")  

bool InforLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InforLayer::onTouchBegan, this);
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
				MainScene::GetMainScene()->SetInfo(_profile->getNormalFile().file);
			}
			//传信息给文件
		});

	//从文件里读信息，我们做一个本地的（dogeq

	//设置头像（To do ：加一个换头像功能？
	_profile = Tools::ButtonCreateN(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.9f), MainScene::GetMainScene()->GetInfo(), this);
	_profile->setScale(1.5);
	_profile->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				int tag = _profile->getNormalFile().file.at(7) - '0';
				auto filename = "ui/info" + Value(tag % kInfos + 1).asString() + ".png";
				_profile->loadTextureNormal(filename);
			}
		});

	//设置info Name
	setInfo(Information::Name, "みけねこ");

	//设置info Cup
	setInfo(Information::Cup, "0");

	//设置info MaxRank
	setInfo(Information::MaxRank, "0");

	//设置info Money
	setInfo(Information::Money, "0");

	return true;
}

void InforLayer::setInfo(Information infoType, const std::string&& info)
{
	if (infoType == Information::Name)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.8f), "昵称", "微软雅黑", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.8f), info, "微软雅黑", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		//这边改名字的话要计入文件里叭.
		_infomation.pushBack(label2);
		_change_name = Tools::ButtonCreate(Vec2(label2->getPosition().x + label2->getContentSize().width + 50, label2->getPosition().y)
			, "ui/edit.png", this);
		_change_name->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					auto item = dynamic_cast<Button*>(ref);
					_text = TextField::create();
					_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
					_text->setPosition(Vec2(item->getPosition().x + item->getContentSize().width / 2 + 15, item->getPosition().y));
					_text->setFontName("微软雅黑");
					_text->setFontSize(36);
					_text->setPlaceHolder("点击这里输入(7字内)");
					this->addChild(_text);
					_text->setMaxLengthEnabled(true);
					_text->setMaxLength(7);
					_text->addEventListener(CC_CALLBACK_2(InforLayer::TextFieldEvent, this));
					/*_text->addClickEventListener([&](Ref* ref)
						{
							dynamic_cast<TextField*>(ref)->setString("");
						});*/
				}});
	}
	else if (infoType == Information::Cup)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.7f), "奖杯", "微软雅黑", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.7f), info, "微软雅黑", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
	else if (infoType == Information::MaxRank)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.6f), "最高排名", "微软雅黑", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.6f), info, "微软雅黑", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
	else if (infoType == Information::Money)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.5f), "金币", "微软雅黑", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.5f), info, "微软雅黑", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
}

void InforLayer::Change(const std::string& newinfo, Information infoType)
{
	if (infoType == Information::Name)
		_infomation.at(0)->setString(newinfo);
}

void InforLayer::TextFieldEvent(Ref* pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		dynamic_cast<TextField*>(pSender)->setString(" ");
		break;
	}
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		auto item = dynamic_cast<TextField*>(pSender);
		Change(item->getString(), Information::Name);
		auto distory = RemoveSelf::create();
		item->runAction(distory);
		break;
	}
	/*case cocos2d::ui::TextField::EventType::INSERT_TEXT:
	{
		auto textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		break;
	}*/

	/*case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		_text->setString("delete word max length %d");
		break;
	}*/

	default:
		break;
	}
}
