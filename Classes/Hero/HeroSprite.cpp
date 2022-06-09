//2150266  ±ÃÏ“›
#include "HeroSprite.h"
#include "Treasure/TreasureBoxSprite.h"
#include "exceptions/unexpected_parent.hpp"
#include <cmath>

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
	}

	std::string intToString(const int number)
	{
		char result[5];
		sprintf(result, "%d", number);

		return result;
	}
}

Hero::Hero(const int originalHP, const int maxAmmo,const Level originalMoveSpeed)
	:_originalHP(originalHP),
	_maxHealthPoint(originalHP),
	_healthPoint(originalHP),
	_originalMoveSpeed(originalMoveSpeed),
	_moveSpeed(originalMoveSpeed),
	_maxAmmo(maxAmmo)
{
}

void Hero::initializeHeroSprite()
{
	_hero = Sprite::create(_heroTexture);
	_hero->setPosition(0, 0);
	this->addChild(_hero);
}

void Hero::initializeHeroPhysics()
{
	auto heroPhysicsBody = PhysicsBody::createBox(_hero->getContentSize());
	heroPhysicsBody->setDynamic(false);
	heroPhysicsBody->setCategoryBitmask(0x1F);
	heroPhysicsBody->setContactTestBitmask(0x1F);
	_hero->setPhysicsBody(heroPhysicsBody);
	_hero->setName("hero");
}

void Hero::initializeBloodStrip()
{
	_bloodStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_bloodStrip->setPercent(100);
	_bloodStrip->setScale(0.18);
	Size heroSize = _hero->getContentSize();
	_bloodStrip->setPosition(Point(0, heroSize.height / 2 + 7));
	this->addChild(_bloodStrip);
}

void Hero::initializeAmmoStrip(int maxAmmo)
{
	//add the picture of ammo strip
	for (int i = 0; i < maxAmmo; i++) {
		Size heroSize = _hero->getContentSize();
		auto strip = Sprite::create("ammoStrip.png");
		_ammoStrip.push_back(strip);
		strip->setPosition(Point(8 * i - 8, heroSize.height / 2 + 2));
		strip->setScale(0.1);
		this->addChild(strip);
	}
}

void Hero::initializeEnergyStrip()
{
	_energyStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_energyStrip->setPercent(0);
	_energyStrip->setScale(0.18);
	_energyStrip->setOpacity(150);
	Size heroSize = _hero->getContentSize();
	_energyStrip->setPosition(Point(0, heroSize.height / 2 + 12));
	this->addChild(_energyStrip);
}

void Hero::initializeDiamondDisplay(const int diamond)
{
	Size heroSize = _hero->getContentSize();
	heroDiamond->setPosition(Point(0, heroSize.height / 2 + 17));
	heroDiamond->setScale(0.6);
	diamondNum = cocos2d::Label::createWithTTF(intToString(diamond), "fonts/Marker Felt.ttf", 5);
	diamondNum->setPosition(Point(5, heroSize.height / 2 + 16));
	this->addChild(heroDiamond);
	this->addChild(diamondNum);
}

void Hero::setAlive(bool alive)
{
	if (alive) {
		_alive = true;
		this->setVisible(true);
		_hero->getPhysicsBody()->setCategoryBitmask(0x1F);
		_hero->setName("hero");
	}
	else {
		_alive = false;
		this->setVisible(false);
		_hero->getPhysicsBody()->setCategoryBitmask(0x00);
		_hero->setName("null");
	}
}

bool Hero::attack(Point target)
{
	//judge the status of hero
	if (!this->alive())
		return false;

	/** modify the ammunition quantity */
	//judge the ammo number
	if (!_ammo)
		return true;

	//check the cool down of attack
	if (this->isScheduled("attack CD"))
		return true;

	//modify attributes
	if (!isScheduled(SEL_SCHEDULE(&Hero::load)))
		schedule(SEL_SCHEDULE(&Hero::load), 2.0 - static_cast<float>(_loadSpeed) * 0.25);
	--_ammo;
	_ammoStrip[_ammo]->setVisible(false);

	//start cool down
	this->scheduleOnce([](float) {}, 0.5, "attack CD");

	//run the animation
	return this->attackAnimation(target);
}

bool Hero::prepareSkillRelease()
{
	if (_energy != _maxEnergy)
		return false;

	if (_energyStrip->getOpacity() == static_cast<uint8_t>(150)) {
		_energyStrip->setOpacity(255);
	}
	else {
		_energyStrip->setOpacity(150);
	}

	return true;
}

bool Hero::releaseSkill(Point target)
{
	//judge the status of hero
	if (!this->alive())
		return false;
	if (!skillStatus())
		return false;

	//modify the energy
	setEnergy(0);

	//run the animation
	return this->skillAnimation(target);
}

void Hero::moveStep(Point target)
{
	//judge whether the hero is moving
	if (_moveSpeed == Level::ZERO)
		return;

	//get the offset
	Vec2 offset = target - this->getPosition();
	offset.normalize();
	offset *= 0.5;

	//query the contact with wall
	bool contactBarrier = false;  ///< judgement
	Point movePos = this->getPosition() + static_cast<int>(_moveSpeed) * offset;  ///< mark the position after moving
	Size heroSize = _hero->getContentSize();  ///< the content size of hero
	Node* parentScene = nullptr;
	if (this->getParent()->getName() == "robot" || this->getParent()->getName() == "player")
		parentScene = this->getParent()->getParent();
	else
		throw unexpected_parent(this->getParent());
	dynamic_cast<Scene*>(parentScene)->getPhysicsWorld()->queryRect(
		PhysicsQueryRectCallbackFunc([&contactBarrier](PhysicsWorld& world, PhysicsShape& shape, void* data)->bool
			{
				//recognize the node
				typedef Node* NodePtr;
				NodePtr wall = nullptr, box = nullptr;
				NodePtr queryNode = shape.getBody()->getNode();
				if (queryNode->getName() == "wall") wall = queryNode;
				if (queryNode->getName() == "box")  box = queryNode;

				//callbacks
				if (wall) {
					contactBarrier = true;
				}
				else if (box) {
					contactBarrier = true;
				}

				return true;
			}),
		Rect(movePos.x - heroSize.width / 2, movePos.y - heroSize.height / 2, heroSize.width, heroSize.height), nullptr);

	//move hero
	if (!contactBarrier) {
		this->setPosition(this->getPosition() + static_cast<int>(_moveSpeed) * offset);
		this->turnTo(offset);
	}
}

void Hero::turnTo(Point target)
{
	//judge whether to rotate
	if (target == Point(0, 0))
		return;

	//record the angle
	float angle = 0;
	if (target.x > 0) {
		angle = 90 - atan(target.y / target.x);
	}
	else if (target.x < 0) {
		angle = 270 - atan(target.y / target.x);
	}
	else {
		if (target.y > 0)
			angle = 0;
		else if (target.y < 0)
			angle = 180;
	}

	//rotation
	_hero->setRotation(angle);
}

int Hero::addHP(int increasePoint)
{
	//exception
	if (increasePoint < 0)
		throw std::out_of_range("negative HP increasement point");
	if (!this->alive())
		return 0;

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
	if (!this->alive())
		return 0;

	//modify the hp
	_healthPoint = (_healthPoint - deductPoint) > 0 ? (_healthPoint - deductPoint) : 0;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	if (_healthPoint) {
		//blood return
		this->unschedule(SEL_SCHEDULE(&Hero::heal));
		this->scheduleOnce(SEL_SCHEDULE(&Hero::heal), 2.0);
	}
	else {
		//remove hero and drop diamonds if blood is empty
		this->setAlive(false);
		scheduleOnce([=](float fdelta)
			{
				for (int i = 0; i < _diamond; i++) {
					auto heroDiamond = TreasureBox::Diamond::dropDiamond(this->getPosition());
					this->getParent()->addChild(heroDiamond);
				}
			}
		, 1.0 / 60, "drop diamond");
	}

	return _healthPoint;
}

int Hero::addEnergy(int increasePoint)
{
	//exception
	if (increasePoint < 0)
		throw std::out_of_range("negative energy increasement point");
	if (!this->alive())
		return 0;

	//modify the energy
	_energy = (_energy + increasePoint) < _maxEnergy ? (_energy + increasePoint) : _maxEnergy;
	_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);

	//update the energy strip and keyboard listener
	if (_energy == _maxEnergy) {
		_energyStrip->setOpacity(255);
	}

	return _energy;
}

int Hero::deductEnergy(int deductPoint)
{
	//exception
	if (deductPoint < 0)
		throw std::out_of_range("negative energy deduction point");
	if (!this->alive())
		return 0;

	//modify the energy
	_energy = (_energy - deductPoint) > 0 ? (_energy - deductPoint) : 0;
	_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);

	//update the energy strip and keyboard listener
	if (_energy != _maxEnergy) {
		_energyStrip->setOpacity(150);
	}

	return _energy;
}

int Hero::setEnergy(const int energy)
{
	//exception
	if (energy < 0)
		throw std::out_of_range("negative energy point");
	else if (energy > _maxEnergy)
		throw std::out_of_range("energy point larger than max energy");
	if (!this->alive())
		return 0;

	//modify the energy
	_energy = energy;

	//update the energy strip
	if (_energy == _maxEnergy) {
		_energyStrip->setOpacity(255);
		_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);
	}
	else {
		_energyStrip->setOpacity(150);
		_energyStrip->setPercent(static_cast<double>(_energy) / _maxEnergy * 100);
	}

	return _energy;
}

int Hero::addDiamond(const int increasePoint)
{
	//exception
	if (increasePoint < 0)
		throw std::out_of_range("negative diamond increasement point");
	if (!this->alive())
		return 0;

	//modify the attribute
	_diamond += increasePoint;
	diamondNum->setString(intToString(_diamond));
	updateAttributesWithDiamond();

	return _diamond;
}

int Hero::deductDiamond(const int deductPoint)
{
	//exception
	if (deductPoint < 0)
		throw std::out_of_range("negative diamond increasement point");
	if (!this->alive())
		return 0;

	//modify the attribute
	_diamond = (_diamond - deductPoint) > 0 ? (_diamond - deductPoint) : 0;
	diamondNum->setString(intToString(_diamond));
	updateAttributesWithDiamond();

	return _diamond;
}

int Hero::setDiamond(const int diamond)
{
	//exception
	if (diamond < 0)
		throw std::out_of_range("negative diamond point");
	if (!this->alive())
		return 0;

	//modify the attribute
	_diamond = diamond;
	diamondNum->setString(intToString(_diamond));
	updateAttributesWithDiamond();

	return _diamond;
}

void Hero::updateAttributesWithDiamond()
{
	_maxHealthPoint = _originalHP + _diamond * 500;
	_healthPoint += _diamond * 500;
	_hitPoint += _diamond * 300;
	_skillHitPoint += _diamond * 200;
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
	this->addHP(709);
}