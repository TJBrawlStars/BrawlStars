#include "GameScene.h"
#include"Hero/HeroSprite.h"
#include"Hero/BeiyaHero.h"
#pragma execution_character_set("utf-8")  

extern std::vector<HeroData> herodataVec;

bool GameScene::init()
{
	if (!Scene::init() || !Scene::initWithPhysics())
		return false;
	//设置场景的tag
	this->setTag(SceneTag::kGameSceneTag);
	
	//开始计时
	auto timer = MyTimer::create();
	this->addChild(timer, kTimerPriority);


	//物理检测红框
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


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
	
	
	this->scheduleUpdate();
	



	return true;
}

/**
* @fn update
* @brief update the position of hero and map
*/
void GameScene::update(float dt)
{
	setViewPointByPlayer(_player->getPosition());

	//
	if (poisonCircleDown->getPosition().y < poisonCircleMax)
	{
		poisonCircleDown->setPosition(poisonCircleDown->getPosition().x, poisonCircleDown->getPosition().y + poisonCircleMarch);
	}

	if (poisonCircleUp->getPosition().y > 0)
	{
		poisonCircleUp->setPosition(poisonCircleUp->getPosition().x, poisonCircleUp->getPosition().y - poisonCircleMarch);
	}

	if (poisonCircleLeft->getPosition().x < poisonCircleMax)
	{
		poisonCircleLeft->setPosition(poisonCircleLeft->getPosition().x + poisonCircleMarch, poisonCircleLeft->getPosition().y );
	}

	if (poisonCircleRight->getPosition().x > 0)
	{
		poisonCircleRight->setPosition(poisonCircleRight->getPosition().x - poisonCircleMarch , poisonCircleRight->getPosition().y );
	}
}


