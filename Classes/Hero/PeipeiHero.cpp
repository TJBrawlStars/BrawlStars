//2150266 Ê±ÌìÒÝ
#include "Hero/PeipeiHero.h"
#include "Factory/HeroFactory.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
	}

	HeroRegister registerCreator(std::string("Peipei"), HeroCreator(Peipei::create));
}

Peipei* Peipei::create()
{
	return new(std::nothrow) Peipei();
}

Peipei::Peipei() :Hero(2400, 3, Level::MEDIUM)
{
	_ammo = _maxAmmo;
	_hitPoint = 800;
	_skillHitPoint = 762;
	_shotRange = Level::EXTREME_HIGH;
	_loadSpeed = Level::EXTREME_LOW;

	this->setHeroTexture("HeroResource/GodPlane.png");
}

bool Peipei::attackAnimation(cocos2d::Point touchLocation)
{
	/** the animation of attack */
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();

	//add projectile
	auto projectile = BulletFactory::getInstance()->createWithClassID("FreezingBullet");
	if (projectile == nullptr)
		problemLoading("FreezingBullet");
	projectile->setHitPoint(this->getHitPoint());
	projectile->setEnergy(_maxEnergy / 3 + 1);
	projectile->setParentHero(this);
	projectile->setPosition(this->getPosition());
	this->getParent()->addChild(projectile);

	//get the vector of attack according to the range of hero
	offset.normalize();
	Vec2 attackVec = offset * 75 * static_cast<int>(_shotRange);

	//create the animation
	auto shot = MoveBy::create(1.2, attackVec);
	auto removeBullet = RemoveSelf::create();
	projectile->runAction(Sequence::create(shot, removeBullet, nullptr));

	return true;
}

bool Peipei::skillAnimation(cocos2d::Point touchLocation)
{
	/** the animation of skill */
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();
	offset.normalize();
	offset *= 75;
	this->setPosition(this->getPosition() + offset);

	return true;
}