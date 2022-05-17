//2150266  ±ÃÏ“›
#include "HeroSprite.h"
#include "Treasure/TreasureBoxSprite.h"
#include <cmath>

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}
}

cocos2d::EventListenerPhysicsContact* Hero::_contactListener = nullptr;

void Hero::setKeyboardListener(bool keyboardState) noexcept
{
	//judge whether the keyboard state needs to be reset
	if (_keyboardListener->isEnabled() == keyboardState)
		return;

	//set the state of keyboardlistener and scheduler
	if (keyboardState) {
		_keyboardListener->setEnabled(true);
		this->schedule(SEL_SCHEDULE(&Hero::moveHero));
	}
	else {
		_keyboardListener->setEnabled(false);
		this->unschedule(SEL_SCHEDULE(&Hero::moveHero));
	}
}

void Hero::setTouchListener(bool touchState) noexcept
{
	//judge whether the touch state needs to be reset
	if (_touchListener->isEnabled() == touchState)
		return;
	else
		_touchListener->setEnabled(touchState);
}

void Hero::setContactListener(bool contactState) noexcept
{
	//judge whether the contact state needs to be reset
	if (_contactListener->isEnabled() == contactState)
		return;
	else
		_contactListener->setEnabled(contactState);
}

Hero::Hero(const int maxHealthPoint, const int maxAmmo)
	:_maxHealthPoint(maxHealthPoint), _maxAmmo(maxAmmo)
{
	//initialize the event listeners
	initializeKeyboardListener();
	initializeTouchListener();
	initializeContactListener();
}

void Hero::initializeKeyboardListener()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
	_keyboardListener->setEnabled(false);
}

void Hero::initializeTouchListener()
{
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(Hero::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
	_touchListener->setEnabled(false);
}

void Hero::initializeContactListener()
{
	if (_contactListener)
		return;
	_contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(Hero::onContactBegin, this);
	_contactListener->onContactSeparate = CC_CALLBACK_1(Hero::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);
}

void Hero::initializeHeroPhysics()
{
	auto heroPhysicsBody = PhysicsBody::createBox(this->getContentSize());
	heroPhysicsBody->setDynamic(false);
	heroPhysicsBody->setCategoryBitmask(0x1F);
	heroPhysicsBody->setContactTestBitmask(0x1F);
	this->setPhysicsBody(heroPhysicsBody);
	this->setName("hero");
}

void Hero::initializeBloodStrip()
{
	_bloodStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_bloodStrip->setPercent(100);
	_bloodStrip->setScale(0.1);
	Size heroSize = this->getContentSize();
	_bloodStrip->setPosition(Point(heroSize.width / 2, heroSize.height + 6));
	this->addChild(_bloodStrip);
}

void Hero::initializeAmmoStrip(int maxAmmo)
{
	//add the picture of ammo strip
	for (int i = 0; i < maxAmmo; i++) {
		Size heroSize = this->getContentSize();
		auto strip = Sprite::create("ammoStrip.png");
		_ammoStrip.push_back(strip);
		strip->setPosition(Point(8 * i, heroSize.height + 3));
		strip->setScale(0.1);
		this->addChild(strip);
	}
}

void Hero::initializeEnergyStrip()
{
	_energyStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_energyStrip->setPercent(0);
	_energyStrip->setScale(0.1);
	_energyStrip->setOpacity(150);
	Size heroSize = this->getContentSize();
	_energyStrip->setPosition(Point(heroSize.width / 2, heroSize.height + 9));
	this->addChild(_energyStrip);
}

/**
* the physics bitmasks:
* name           categoryBitmask         contactTestBitmask
* hero           0x1F                    0x1F
* bullet         0x03                    0x03
* wall           0x01                    0x01
* grass          0x04                    0x04
* diamond        0x08                    0x08
* box            0x02                    0x02
* poison         0x10                    0x10
*/
bool Hero::onContactBegin(PhysicsContact& contact)
{
	//distinguish the nodes
	typedef Node* NodePtr;
	NodePtr hero = nullptr, bullet = nullptr, wall = nullptr, grass = nullptr, diamond = nullptr, box = nullptr;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getName() == "hero") hero = nodeA;
	if (nodeB->getName() == "hero") hero = nodeB;
	if (nodeA->getName() == "bullet") bullet = nodeA;
	if (nodeB->getName() == "bullet") bullet = nodeB;
	if (nodeA->getName() == "wall") wall = nodeA;
	if (nodeB->getName() == "wall") wall = nodeB;
	if (nodeA->getName() == "grass") grass = nodeA;
	if (nodeB->getName() == "grass") grass = nodeB;
	if (nodeA->getName() == "diamond") diamond = nodeA;
	if (nodeB->getName() == "diamond") diamond = nodeB;
	if (nodeA->getName() == "box") box = nodeA;
	if (nodeB->getName() == "box") box = nodeB;

	//handle the contacts
	if (hero && bullet) {
		//make sure the bullet wont hit its parent hero
		if (dynamic_cast<Hero*>(hero) == dynamic_cast<Bullet*>(bullet)->getParentHero())
			return false;

		//deduct hp
		dynamic_cast<Hero*>(hero)->deductHP(dynamic_cast<Bullet*>(bullet)->getHitPoint());

		//add energy
		dynamic_cast<Bullet*>(bullet)->getParentHero()->increaseEnergy(dynamic_cast<Bullet*>(bullet)->getEnergy());

		//remove bullet
		bullet->getPhysicsBody()->setCategoryBitmask(0x00);
		bullet->setVisible(false);

		//blood return
		hero->unschedule(SEL_SCHEDULE(&Hero::heal));
		hero->scheduleOnce(SEL_SCHEDULE(&Hero::heal), 2.0);

		return false;
	}
	else if (hero && diamond) {
		//add diamond
		dynamic_cast<Hero*>(hero)->_diamond++;
		diamond->getPhysicsBody()->setCategoryBitmask(0x00);
		diamond->setVisible(false);

		return false;
	}
	else if (hero && grass) {
		//make hero transparent
		hero->setOpacity(150);
		grass->setOpacity(150);

		return false;
	}
	else if (bullet && wall) {
		//remove bullet
		bullet->getPhysicsBody()->setCategoryBitmask(0x00);
		bullet->setVisible(false);

		return false;
	}
	else if (bullet && box) {
		//deduct box hp and remove bullet
		dynamic_cast<TreasureBox::Box*>(box)->deductHP(dynamic_cast<Bullet*>(bullet)->getHitPoint());
		bullet->getPhysicsBody()->setCategoryBitmask(0x00);
		bullet->setVisible(false);

		return false;
	}

	return false;
}

void Hero::onContactSeperate(PhysicsContact& contact)
{
	//distinguish the nodes
	typedef Node* NodePtr;
	NodePtr hero = nullptr, bullet = nullptr, wall = nullptr, grass = nullptr, diamond = nullptr;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getName() == "hero") hero = nodeA;
	if (nodeB->getName() == "hero") hero = nodeB;
	if (nodeA->getName() == "bullet") bullet = nodeA;
	if (nodeB->getName() == "bullet") bullet = nodeB;
	if (nodeA->getName() == "wall") wall = nodeA;
	if (nodeB->getName() == "wall") wall = nodeB;
	if (nodeA->getName() == "grass") grass = nodeA;
	if (nodeB->getName() == "grass") grass = nodeB;
	if (nodeA->getName() == "diamond") diamond = nodeA;
	if (nodeB->getName() == "diamond") diamond = nodeB;

	if (hero && grass) {
		//make hero and grass visible
		hero->setOpacity(255);
		grass->setOpacity(255);
	}
	if (hero && diamond) {
		diamond->getParent()->removeFromParent();
	}
}

void Hero::moveHero(float fdelta)
{
	using code = cocos2d::EventKeyboard::KeyCode;

	//judge whether the hero is moving
	if (_moveSpeed == Level::ZERO)
		return;

	//record the offset of coordinate
	int offsetX = 0, offsetY = 0;
	if (_keyCodeState[code::KEY_W] == true)
		offsetY = 1;
	else if (_keyCodeState[code::KEY_S] == true)
		offsetY = -1;
	if (_keyCodeState[code::KEY_A] == true)
		offsetX = -1;
	else if (_keyCodeState[code::KEY_D] == true)
		offsetX = 1;

	//normalize the offset
	Vec2 offset = Vec2(offsetX, offsetY);
	offset.normalize();
	offset *= 0.5;

	//move the hero
	this->setPosition(this->getPosition() + static_cast<int>(_moveSpeed) * offset);
}

void Hero::superchargedAbility(float fdelta)
{

}

int Hero::increaseHP(int increasePoint)
{
	//exception
	if (increasePoint < 0)
		throw std::out_of_range("negative HP increasement point");

	//modify the hp
	_healthPoint = (_healthPoint + increasePoint) < _maxHealthPoint ? (_healthPoint + increasePoint) : _maxHealthPoint;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	return _healthPoint;
}

int Hero::deductHP(int deductPoint)
{
	//exception
	if (deductPoint < 0)
		throw std::out_of_range("negative HP deduction point");

	//modify the hp
	_healthPoint = (_healthPoint - deductPoint) > 0 ? (_healthPoint - deductPoint) : 0;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	return _healthPoint;
}

int Hero::increaseEnergy(int increasePoint)
{
	//exception
	if (increasePoint < 0)
		throw std::out_of_range("negative energy increasement point");

	//modify the energy
	_energy = (_energy + increasePoint) < _maxEnergy ? (_energy + increasePoint) : _maxEnergy;
	_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);

	if (_energy == _maxEnergy)
		_energyStrip->setOpacity(255);

	return _energy;
}

int Hero::deductEnergy(int deductPoint)
{
	//exception
	if (deductPoint < 0)
		throw std::out_of_range("negative energy deduction point");

	//modify the energy
	_energy = (_energy - deductPoint) > 0 ? (_energy - deductPoint) : 0;
	_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);

	//update the energy strip
	if (_energy != _maxEnergy)
		_energyStrip->setOpacity(150);

	return _energy;
}

int Hero::setEnergy(const int energy)
{
	//exception
	if (energy < 0)
		throw std::out_of_range("negative energy point");
	else if (energy > _maxEnergy)
		throw std::out_of_range("energy point larger than max energy");

	//modify the energy
	_energy = energy;

	//update the energy strip
	if (_energy == _maxEnergy)
		_energyStrip->setOpacity(255);
	else
		_energyStrip->setOpacity(150);

	return _energy;
}

void Hero::load(float fdelta) noexcept
{
	_ammo = (_ammo + 1) < _maxAmmo ? (_ammo + 1) : _maxAmmo;
	_ammoStrip[_ammo - 1]->setVisible(true);
}

void Hero::heal(float fdelta) noexcept
{
	if (!isScheduled(SEL_SCHEDULE(&Hero::heal)))
		schedule(SEL_SCHEDULE(&Hero::heal), 0.75);
	this->_healthPoint = (_healthPoint + 709) < _maxHealthPoint ? (_healthPoint + 709) : _maxHealthPoint;
	this->_bloodStrip->setPercent(static_cast<float>(_healthPoint) / _maxHealthPoint * 100);
}