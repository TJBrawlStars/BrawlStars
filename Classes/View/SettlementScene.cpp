#include "SettlementScene.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include"Tool/Tools.h"
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

    //从游戏控制器中读出我方和敌方的hero然后把照片贴上来,然后对应的战绩也要有,在底下+标签叭

	//从游戏控制器中读出胜利方，然后在指定一边显示win
	WhoWin();

	return true;
}

void SettlementScene::WhoWin()
{
	//读游戏控制器的操作，这边就先直接我方win叭
	auto win = true;

	auto label = Label::createWithTTF("W I N", "fonts/arial.ttf", 75);
	assert(label != 0);
	this->addChild(label);

	if (win)
		label->setPosition(Vec2(kVisibleSize.width / 2 - 450, kVisibleSize.height - 100));
	else
		label->setPosition(Vec2(kVisibleSize.width / 2 + 450, kVisibleSize.height - 100));
}

void SettlementScene::ShowRecord()
{
	//用for的那个用法批量创建图片
	//同上，批量创建label，都写在TOOl里叭，那个类名字改一下
}
