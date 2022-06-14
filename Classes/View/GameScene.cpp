#include "GameScene.h"
#pragma execution_character_set("utf-8")  

extern std::vector<HeroData> herodataVec;

bool GameScene::init()
{
	if (!Scene::init() || !Scene::initWithPhysics())
		return false;

	//初始化地图
	addMap(cocos2d::random(1,3)); 
	//初始化障碍层
	addBarrier();
	//初始化草丛
	addGrass();
	//添加主角
	addHeroPlayer();
	//添加宝箱
	addBox();
	//添加毒圈
	addPoisonCircle();
	//添加计时器
	//addTimer();
	//添加聊天室
	addChatBox();
	//添加物理引擎碰撞检测
	initializeContactListener();
	//添加聊天框监听
	initTouchAndKeyListener();
	

	this->scheduleUpdate();
	
	return true;
}

/**
* @fn update
* @brief update the position of hero and map
*/
void GameScene::update(float dt)
{
	//跟随主角
	setViewPointByPlayer(_player->getPosition());

	//更新 计时器 聊天室
	//updateMyTimerPosition();
	updateChatBoxPosition();
	updateLeaderBoard();
	//grassPlayerOpacity();

	//if (!_player->alive())
	//{
	//	SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_SettlementScene);
	//}

	if (poisonCircleDown->getPosition().y > poisonCircleMax / 2)
	{
		poisonCircleDown->setPosition(poisonCircleDown->getPosition().x, poisonCircleDown->getPosition().y - poisonCircleMarch);
	}
	if (poisonCircleUp->getPosition().y < poisonCircleMax / 2)
	{
		poisonCircleUp->setPosition(poisonCircleUp->getPosition().x, poisonCircleUp->getPosition().y + poisonCircleMarch);
	}
	if (poisonCircleLeft->getPosition().x > poisonCircleMax / 2)
	{
		poisonCircleLeft->setPosition(poisonCircleLeft->getPosition().x - poisonCircleMarch, poisonCircleLeft->getPosition().y);
	}
	if (poisonCircleRight->getPosition().x < poisonCircleMax / 2)
	{
		poisonCircleRight->setPosition(poisonCircleRight->getPosition().x + poisonCircleMarch, poisonCircleRight->getPosition().y);
	}
}


