#include "cocos2d.h"
#include "Const/Const.h"
#include "Item.h"
USING_NS_CC;

void Item::bindSprite(Sprite* sprite)
{
	_sprite = sprite;

}

Sprite* Item::getSprite()
{
	return _sprite;
}

void Item::generatePhysicalBody(std::string message, int itemTag)
{
	_sprite->setTag(itemTag);
	auto size = _sprite->getContentSize();
	size.width *= 1.2;
	size.height *= 1.2;
	auto body = cocos2d::PhysicsBody::createBox(size);
	body->setDynamic(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(1);
	body->setContactTestBitmask(1);
	_sprite->setPhysicsBody(body);

	//ÔÝ²»ÊµÏÖ
	//auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(Item::onContactBegin, this);
	//contactListener->onContactSeparate = CC_CALLBACK_1(Item::onContactSeparate, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}