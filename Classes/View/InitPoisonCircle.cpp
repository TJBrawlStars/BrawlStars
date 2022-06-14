//2152590 ����

#include "View/GameScene.h"

void GameScene::addPoisonCircle()
{
	poisonCircleDown = cocos2d::Sprite::create("poisoncircle/circledown.png");
	poisonCircleDown->setPosition(1200,2400);
	poisonCircleDown->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	this->addChild(poisonCircleDown);
	poisonCircleDown->setGlobalZOrder(kpoisonPriority);
	initializePoiosnPhysics(poisonCircleDown);

	poisonCircleUp = cocos2d::Sprite::create("poisoncircle/circleup.png");
	poisonCircleUp->setPosition(1200, 0);
	poisonCircleUp->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	this->addChild(poisonCircleUp);
	poisonCircleUp->setGlobalZOrder(kpoisonPriority);
	initializePoiosnPhysics(poisonCircleUp);

	poisonCircleLeft = cocos2d::Sprite::create("poisoncircle/circleleft.png");
	poisonCircleLeft->setPosition(2400, 1200);
	poisonCircleLeft->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	this->addChild(poisonCircleLeft);
	poisonCircleLeft->setGlobalZOrder(kpoisonPriority);
	initializePoiosnPhysics(poisonCircleLeft);

	poisonCircleRight = cocos2d::Sprite::create("poisoncircle/circleright.png");
	poisonCircleRight->setPosition(0, 1200);
	poisonCircleRight->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_RIGHT);
	this->addChild(poisonCircleRight);
	poisonCircleRight->setGlobalZOrder(kpoisonPriority);
	initializePoiosnPhysics(poisonCircleRight);
}




void GameScene::initializePoiosnPhysics(cocos2d::Sprite* poison)
{
	auto poisonPhysicsBody = PhysicsBody::createBox(poison->getContentSize());
	poisonPhysicsBody->setDynamic(false);
	poisonPhysicsBody->setCategoryBitmask(0x10);
	poisonPhysicsBody->setContactTestBitmask(0x10);
	poison->setPhysicsBody(poisonPhysicsBody);
	poison->setName("poison");
}