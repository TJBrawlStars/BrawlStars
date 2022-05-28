//2152590 ЭѕСе

#include "View/GameScene.h"

void GameScene::addPoisonCircle()
{
	poisonCircleDown = cocos2d::Sprite::create("poisoncircle/circledown.png");
	poisonCircleDown->setPosition(1200, -1224);
	this->addChild(poisonCircleDown);
	initializePoiosnPhysics(poisonCircleDown);

	poisonCircleUp = cocos2d::Sprite::create("poisoncircle/circleup.png");
	poisonCircleUp->setPosition(1200, 2400+1200);
	this->addChild(poisonCircleUp);
	initializePoiosnPhysics(poisonCircleUp);

	poisonCircleLeft = cocos2d::Sprite::create("poisoncircle/circleleft.png");
	poisonCircleLeft->setPosition(-1204, 1200);
	this->addChild(poisonCircleLeft);
	initializePoiosnPhysics(poisonCircleLeft);

	poisonCircleRight = cocos2d::Sprite::create("poisoncircle/circleright.png");
	poisonCircleRight->setPosition(2400+1200, 1200);
	this->addChild(poisonCircleRight);
	initializePoiosnPhysics(poisonCircleRight);
}




void GameScene:: initializePoiosnPhysics(cocos2d::Sprite* poison)
{
	auto poisonPhysicsBody = PhysicsBody::createBox(poison->getContentSize());
	poisonPhysicsBody->setDynamic(false);
	poisonPhysicsBody->setCategoryBitmask(0x10);
	poisonPhysicsBody->setContactTestBitmask(0x10);
	poison->setPhysicsBody(poisonPhysicsBody);
	poison->setName("poison");
}