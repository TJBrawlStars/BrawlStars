#include "SettlementScene.h"
#pragma execution_character_set("utf-8")  

bool SettlementScene::init()
{
	if (!Scene::init())
		return false;

	_continue = Button::create("CloseNormal.png");
	assert(_continue);
	_continue->setPosition(kVisibleSize / 2);
	this->addChild(_continue);
	_continue->addClickEventListener([](Ref*)
		{
			SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_MainScene);
		});

	auto label = Label::createWithSystemFont("结算界面", "方正姚体", 50);
	assert(label);
	label->setPosition(kVisibleSize.x / 2, kVisibleSize.y / 2 - 100);
	this->addChild(label);

	return true;
}
