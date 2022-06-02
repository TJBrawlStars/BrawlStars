#include "InforLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/Setting.h"
#include"Tool/Tools.h"
#include "MainScene.h"
#include "Tool/Data.h"
#pragma execution_character_set("utf-8")  

bool InforLayer::init()
{
	if (!Layer::init())
		return false;

	//�������ɵ���¼�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InforLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//����
	_bg = Tools::SetBg(this);

	//���ذ�ť
	_back = Tools::ButtonCreate(Vec2(100, kVisibleSize.height - 100), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Tools::SwitchScene(this, Tools::SwitchSceneType::Up);
				MainScene::GetMainScene()->SetInfo(_profile->getNormalFile().file);
			}
			//����Ϣ���ļ�
		});

	//���ļ������Ϣ��������һ�����صģ�dogeq

	//����ͷ��To do ����һ����ͷ���ܣ�
	_profile = Tools::ButtonCreateN(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.9f)
		, PlistData::getDataByType(PlistData::DataType::Profile), this);
	_profile->setScale(1.5);
	_profile->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				int tag = _profile->getNormalFile().file.at(7) - '0';
				auto filename = "ui/info" + Value(tag % kInfos + 1).asString() + ".png";
				_profile->loadTextureNormal(filename);
				PlistData::WriteDataByType(PlistData::DataType::Profile, filename);
			}
		});

	//����info Name
	setInfo(Information::Name, PlistData::getDataByType(PlistData::DataType::Name));

	//����info Cup
	setInfo(Information::Cup, PlistData::getDataByType(PlistData::DataType::Cups));

	//����info MaxRank
	setInfo(Information::MaxRank, "0");

	//����info Money
	setInfo(Information::Money, PlistData::getDataByType(PlistData::DataType::Money));

	return true;
}

void InforLayer::setInfo(Information infoType, const std::string&& info)
{
	if (infoType == Information::Name)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.8f), "�ǳ�", "΢���ź�", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.8f), info, "΢���ź�", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		//��߸����ֵĻ�Ҫ�����ļ����.
		_infomation.pushBack(label2);
		_change_name = Tools::ButtonCreate(Vec2(label2->getPosition().x + label2->getContentSize().width + 50, label2->getPosition().y)
			, "ui/edit.png", this);
		_change_name->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					auto item = dynamic_cast<Button*>(ref);
					_text = Tools::TextCreate(Vec2(item->getPosition().x + item->getContentSize().width / 2 + 15, item->getPosition().y)
						, "�����������(7����)", 8, this);
					_text->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
					_text->addEventListener(CC_CALLBACK_2(InforLayer::TextFieldEvent, this));
				}});
	}
	else if (infoType == Information::Cup)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.7f), "����", "΢���ź�", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.7f), info, "΢���ź�", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
	else if (infoType == Information::MaxRank)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.6f), "�������", "΢���ź�", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.6f), info, "΢���ź�", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
	else if (infoType == Information::Money)
	{
		auto label1 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 - 25, kVisibleSize.height * 0.5f), "���", "΢���ź�", 40, this);
		label1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		auto label2 = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2 + 25, kVisibleSize.height * 0.5f), info, "΢���ź�", 40, this);
		label2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_infomation.pushBack(label2);
	}
}

void InforLayer::Change(const std::string& newinfo, Information infoType)
{
	if (infoType == Information::Name)
	{
		_infomation.at(0)->setString(newinfo);
		PlistData::WriteDataByType(PlistData::DataType::Name, newinfo);
		_change_name->setPosition(Vec2(_infomation.at(0)->getPosition().x + _infomation.at(0)->getContentSize().width + 50, _infomation.at(0)->getPosition().y));
	}
}

void InforLayer::TextFieldEvent(Ref* pSender, cocos2d::ui::TextField::EventType type)
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
		auto name = item->getString();
		Change(name.substr(1, name.size() - 1), Information::Name);
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