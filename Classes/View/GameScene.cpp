#include "GameScene.h"
#include"Hero/HeroSprite.h"
#include"Hero/BeiyaHero.h"
#pragma execution_character_set("utf-8")  

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	//这是王佳垚写的，我先停掉了，停在我这个地图界面

	/*auto label = Label::createWithSystemFont("游戏界面", "方正姚体", 50);
	assert(label);
	label->setPosition(kVisibleSize.x / 2, kVisibleSize.y / 2 - 100);
	this->addChild(label);

	auto _continue = Button::create("CloseNormal.png");
	assert(_continue);
	_continue->setPosition(kVisibleSize / 2);
	this->addChild(_continue);
	_continue->addClickEventListener([](Ref*)
		{
			SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_SettlementScene);
		});*/

	//初始化地图
	initMap();

	

	// Add BeiyaHero
	_player = Beiya::createBeiya();
	_player->setPosition(Vec2(100, 100));
	this->addChild(_player);
	this->scheduleUpdate();
	
	return true;
}

/**
* @fn update
* @brief update 
*/
void GameScene::update(float dt)
{
	//use the keyboard to move hero
	_player->setKeyboardListener(true);
	setViewPointByPlayer(_player->getPosition());

	//test zjk
	isColliding(_player->getPosition());
}