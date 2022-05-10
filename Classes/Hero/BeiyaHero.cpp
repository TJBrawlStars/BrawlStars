//2150266 Ê±ÌìÒÝ
#include "Hero/BeiyaHero.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}
}

Beiya* Beiya::createBeiya()
{
	Beiya* beiya = new(std::nothrow) Beiya();
	if (beiya && beiya->initWithFile(_beiyaPicture))
	{
		beiya->autorelease();

		//initialize the physics body
		beiya->initializeHeroPhysics(beiya);

		//draw the blood strip
		beiya->initialzeBloodStrip(beiya->_maxHealthPoint);

		//draw the ammo strip
		beiya->initializeAmmoStrip(beiya->_maxAmmo);

		return beiya;
	}
	else
	{
		delete beiya;
		beiya = nullptr;
		return nullptr;
	}

	return beiya;
}

const std::string Beiya::_beiyaPicture = "player.png";

Beiya::Beiya() :Hero(3360, 1)
{
	_healthPoint = _maxHealthPoint;
	_ammo = _maxAmmo;
	_hitPoint = 1120;
	_moveSpeed = Level::MEDIUM;
	_shotRange = Level::HIGH;
	_loadSpeed = Level::EXTREME_HIGH;
}

bool Beiya::attack(Touch* touch, Event* event)
{
	if (!_ammo)
		return true;

	/** the animation of attack */
	//get the location of touch point
	Point touchLocation = touch->getLocation();
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();

	//add projectile
	auto projectile = Bullet::createBullet("projectile.png");
	if (projectile == nullptr)
		problemLoading("projectile.png");
	projectile->sethitPoint(this->getHitPoint());
	projectile->setPosition(this->getPosition());
	initializeBulletPhysics(projectile);
	this->getParent()->addChild(projectile);

	//get the vector of attack according to the range of hero
	offset.normalize();
	Vec2 attackVec = offset * 50 * static_cast<int>(_shotRange);

	//create the animation
	auto shot = MoveBy::create(static_cast<float>(_shotRange) / 5, attackVec);
	auto removeBullet = RemoveSelf::create();
	projectile->runAction(Sequence::create(shot, removeBullet, nullptr));

	//modify the ammunition quantity
	if (!isScheduled(SEL_SCHEDULE(&Hero::startLoading)))
		schedule(SEL_SCHEDULE(&Hero::startLoading), 2.0 - static_cast<float>(_loadSpeed) * 0.25);
	--_ammo;
	_ammoStrip[_ammo]->setVisible(false);

	return true;
}