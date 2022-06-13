//2150266 时天逸
#include "Hero/BeiyaHero.h"
#include "Factory/HeroFactory.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
	}

	HeroRegister registerCreator(std::string("Beiya"), HeroCreator(Beiya::create));
}

Beiya* Beiya::create()
{
	return new(std::nothrow) Beiya();
}

Beiya::Beiya() :Hero(3360, 1, Level::MEDIUM)
{
	_ammo = _maxAmmo;
	_hitPoint = 1120;
	_skillHitPoint = 762;
	_shotRange = Level::HIGH;
	_loadSpeed = Level::EXTREME_HIGH;

	this->setHeroTexture("HeroResource/GodPlane.png");
}

bool Beiya::attackAnimation(cocos2d::Point touchLocation)
{
	/** the animation of attack */
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();

	//add projectile
	auto projectile = BulletFactory::getInstance()->createWithClassID("NormalBullet");
	if (projectile == nullptr)
		problemLoading("NormalBullet");
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

bool Beiya::skillAnimation(cocos2d::Point touchLocation)
{
	/** the animation of skill */
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();
	offset.normalize();

	//the animation of skill
	Bullet* bullet[5];
	std::string bulletNo[5] = { "1","2","3","4","5" };
	int count = 1;
	for (auto i : bullet) {
		//create a bullet
		i = BulletFactory::getInstance()->createWithClassID("NormalBullet");
		if (i == nullptr)
			problemLoading("NormalBullet");
		i->setHitPoint(this->getSkillHitPoint());
		i->setEffect(Bullet::Effect::NONE);
		i->setParentHero(this);
		this->getParent()->addChild(i);
		i->setVisible(false);
		this->scheduleOnce(
			[=](float fdelta)
			{
				i->setPosition(this->getPosition());
				i->setVisible(true);
				Vec2 attackVec = offset * 75 * static_cast<int>(_shotRange);
				auto shot = MoveBy::create(static_cast<float>(_shotRange) / 3, attackVec);
				auto removeBullet = RemoveSelf::create();
				i->runAction(Sequence::create(shot, removeBullet, nullptr));
			}
		, 0.2 * count, bulletNo[count - 1]);
		
		count++;
	}

	return true;
}