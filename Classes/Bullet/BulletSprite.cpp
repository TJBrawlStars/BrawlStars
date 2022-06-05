//2150266 Ê±ÌìÒÝ
#include "Bullet/BulletSprite.h"
#include "Treasure/TreasureBoxSprite.h"

USING_NS_CC;

bool Bullet::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;

    return true;
}

void Bullet::initializeBulletPhysics()
{
    auto bulletPhysicsBody = PhysicsBody::createBox(this->getContentSize());
    bulletPhysicsBody->setDynamic(false);
    bulletPhysicsBody->setCategoryBitmask(0x03);
    bulletPhysicsBody->setContactTestBitmask(0x03);
    this->setPhysicsBody(bulletPhysicsBody);
    this->setName("bullet");
}

void Bullet::initializeContactListener()
{
	if (_initContactListener)
		return;
	_contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(Bullet::onContactBegin, this);
	_contactListener->onContactSeparate = CC_CALLBACK_1(Bullet::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);
	_initContactListener = true;
}

bool Bullet::onContactBegin(PhysicsContact& contact)
{
	//distinguish the nodes
	typedef Node* NodePtr;
	NodePtr hero = nullptr, bullet = nullptr;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getName() == "hero")    hero = nodeA->getParent();
	if (nodeB->getName() == "hero")    hero = nodeB->getParent();
	if (nodeA->getName() == "bullet")  bullet = nodeA;
	if (nodeB->getName() == "bullet")  bullet = nodeB;

	//handle the physics contact of this object
	if (bullet != this)
		return true;

	//handle the contacts
	if (hero && bullet) {
		//make sure the bullet wont hit its parent hero
		if (dynamic_cast<Hero*>(hero) == this->getParentHero())
			return false;

		//deduct hp
		dynamic_cast<Hero*>(hero)->deductHP(this->getHitPoint());

		//add energy
		this->getParentHero()->addEnergy(dynamic_cast<Bullet*>(bullet)->getEnergy());

		//the bullet effect
		this->bulletEffect(dynamic_cast<Hero*>(hero));

		//remove bullet
		dynamic_cast<Bullet*>(bullet)->setExist(false);
		dynamic_cast<Bullet*>(bullet)->effectAnimation();

		return false;
	}

	return false;
}

void Bullet::onContactSeperate(PhysicsContact& contact)
{
	return;

	//distinguish the nodes
	typedef Node* NodePtr;
	NodePtr hero = nullptr, bullet = nullptr;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getName() == "hero")    hero = nodeA;
	if (nodeB->getName() == "hero")    hero = nodeB;
	if (nodeA->getName() == "bullet")  bullet = nodeA;
	if (nodeB->getName() == "bullet")  bullet = nodeB;
}

void Bullet::setExist(bool exist) noexcept
{
	if (exist) {
		this->getPhysicsBody()->setCategoryBitmask(0x03);
		this->setVisible(true);
	}
	else {
		this->getPhysicsBody()->setCategoryBitmask(0x00);
		this->setVisible(false);
	}
}