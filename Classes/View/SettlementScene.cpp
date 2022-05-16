#include "SettlementScene.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include"Tool/Tools.h"
#include"Tool/Data.h"
#pragma execution_character_set("utf-8")  

bool SettlementScene::init()
{
	if (!Scene::init())
		return false;

	//背景
	_bg = Tools::SetBg("ui/settlementBg.png", this);

    //继续按钮
	_continue = Tools::ButtonCreate("继 续", Vec2(kVisibleSize.width / 2, 70), this);
	_continue->addClickEventListener([](Ref*)
		{
			SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_MainScene);
		});

	//从游戏控制器中读出排名数据，
	Win();

	//角色形象
	_figure = Tools::SetBg(PlistData::getDataByType(PlistData::DataType::Figure), this);

	return true;
}

void SettlementScene::Win()
{
	//读游戏控制器的操作，这边就先直接win叭
	std::string ranking = "1";
	assert(Value(ranking).asInt() <= 10 && Value(ranking).asInt() >= 1);

	//获得奖杯数目
	auto cupslabel = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.9f), "获得奖杯", "微软雅黑", 35, this);
	cupslabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	_cups= Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.9f), "", "微软雅黑", 35, this);
	_cups->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	//获得金币数量(根据模式不同改变，但只有一个模式就定100叭)
	auto moneylabel = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.8f), "获得金币", "微软雅黑", 35, this);
	moneylabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	_money = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.8f), "   100", "微软雅黑", 35, this);
	_money->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	PlistData::WriteDataByType(PlistData::DataType::Money, Value(Value(PlistData::getDataByType(PlistData::DataType::Money)).asInt() + 100).asString());

	if (ranking == "1")
	{
		auto label = Tools::LabelCreateTTF(Vec2(kVisibleSize.width / 2 - 450, kVisibleSize.height - 100), "W I N", "fonts/arial.ttf", 75, this);
		_cups->setString("   2");
		PlistData::WriteDataByType(PlistData::DataType::Cups, Value(Value(PlistData::getDataByType(PlistData::DataType::Cups)).asInt() + 2).asString());
	}
	else
	{
		auto label = Tools::LabelCreateTTF(Vec2(kVisibleSize.width / 2 - 450, kVisibleSize.height - 100), "第 " + ranking + " 名", "fonts/arial.ttf", 75, this);
		if (Value(ranking).asInt() <= 3)
		{
			_cups->setString("   1");
			PlistData::WriteDataByType(PlistData::DataType::Cups, Value(Value(PlistData::getDataByType(PlistData::DataType::Cups)).asInt() + 1).asString());
		}
		else if (Value(ranking).asInt() <= 6)
			_cups->setString("   0");
		else
		{
			_cups->setString("   -1");
			PlistData::WriteDataByType(PlistData::DataType::Cups, Value(Value(PlistData::getDataByType(PlistData::DataType::Cups)).asInt() - 1).asString());
		}
	}
}
