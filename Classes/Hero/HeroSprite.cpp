//2150266 Ê±ÌìÒÝ
 #include "HeroSprite.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}
}

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
	_contactListener = EventListenerPhysicsContact::create();
	_contactListener->onContactBegin = CC_CALLBACK_1(Hero::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);
	_contactListener->setEnabled(false);
}

void Hero::initializeHeroPhysics(cocos2d::Sprite* hero)
{
	auto heroPhysicsBody = PhysicsBody::createBox(hero->getContentSize());
	heroPhysicsBody->setDynamic(false);
	heroPhysicsBody->setCategoryBitmask(0x01);
	heroPhysicsBody->setContactTestBitmask(0x01);
	hero->setPhysicsBody(heroPhysicsBody);
	hero->setName("hero");
}

void Hero::initializeBulletPhysics(cocos2d::Sprite* bullet)
{
	auto bulletPhysicsBody = PhysicsBody::createBox(bullet->getContentSize());
	bulletPhysicsBody->setDynamic(false);
	bulletPhysicsBody->setCategoryBitmask(0x01);
	bulletPhysicsBody->setContactTestBitmask(0x01);
	bullet->setPhysicsBody(bulletPhysicsBody);
	bullet->setName("bullet");
}

void Hero::initialzeBloodStrip(int healthPoint)
{
	_bloodStrip = ui::LoadingBar::create("bloodStrip.png");
	_bloodStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_bloodStrip->setPercent(100);
	_bloodStrip->setScale(0.1);
	Size heroSize = this->getContentSize();
	_bloodStrip->setPosition(Point(heroSize.width / 2, heroSize.height + 4));
	this->addChild(_bloodStrip);
}

bool Hero::onContactBegin(PhysicsContact& contact)
{
	//distinguish the nodes
	Node* hero = nullptr;
	Node* bullet = nullptr;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getName() == "hero") hero = nodeA;
	if (nodeB->getName() == "hero") hero = nodeB;
	if (nodeA->getName() == "bullet") bullet = nodeA;
	if (nodeB->getName() == "bullet") bullet = nodeB;

	//judge whether should the contact be handled
	if (hero == nullptr || bullet == nullptr)
		return false;
	if (hero == this)
		return false;

	dynamic_cast<Hero*>(hero)->deductHP(dynamic_cast<Hero*>(bullet->getParent())->getHitPoint());
	bullet->removeFromParentAndCleanup(true);

	return true;
}

void Hero::moveHero(float fdelta)
{
	using code = cocos2d::EventKeyboard::KeyCode;

	//judge whether the hero is frozen
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

	//create the animation
	auto move = MoveBy::create(0.1, static_cast<int>(_moveSpeed) * offset * 0.5);
	this->runAction(move);
}

void Hero::startLoading(float fdelta)
{
	//add the function to scheduler
	if (!isScheduled(SEL_SCHEDULE(&Hero::startLoading)))
		this->schedule(SEL_SCHEDULE(&Hero::startLoading), 0.75f);

	//remove from scheduler if is full of bullet
	if (_ammo == _maxAmmo) {
		this->setTouchListener(true);
		this->unschedule(SEL_SCHEDULE(&Hero::startLoading));
		return;
	}

	//loading
	if (!_ammo) {
		this->setTouchListener(false);
		_ammo += 1;
		return;
	}
	else {
		this->setTouchListener(true);
		_ammo += 1;
		return;
	}
}

int Hero::increaseHP(int increasePoint)
{
	if (increasePoint < 0)
		throw std::out_of_range("negative HP increasement point");

	_healthPoint = (_healthPoint + increasePoint) < 100 ? (_healthPoint + increasePoint) : 100;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	return _healthPoint;
}

int Hero::deductHP(int deductPoint)
{
	if (deductPoint < 0)
		throw std::out_of_range("negative HP deduction point");

	_healthPoint = (_healthPoint - deductPoint) > 0 ? (_healthPoint - deductPoint) : 0;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	return _healthPoint;
}