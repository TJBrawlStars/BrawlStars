//2152590 ЭѕСе
#include "Hero/XueliHero.h"
#include "Factory/HeroFactory.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
	}

	HeroRegister registerCreator(std::string("Xueli"), HeroCreator(Xueli::create));
}

Xueli* Xueli::create()
{
	return new(std::nothrow)  Xueli();
}

Xueli::Xueli() :Hero(3360, 1, Level::MEDIUM)
{
	_ammo = _maxAmmo;
	_hitPoint = 725;
	_skillHitPoint = 3312;
	_shotRange = Level::HIGH;
	_loadSpeed = Level::MEDIUM;

	this->setHeroTexture("HeroResource/ToonPlane.png");

}

bool Xueli::attackAnimation(cocos2d::Point touchLocation)
{
	/** the animation of attack */

	//convert the location to offset
	Vec2 offset_fir = touchLocation - this->getPosition();
	Vec2 offset_sec = Vec2(touchLocation.x ,touchLocation.y + 50.0f) - this->getPosition();
	Vec2 offset_thi = Vec2(touchLocation.x, touchLocation.y - 50.0f) - this->getPosition();

	//get the vector of attack according to the range of hero
	offset_fir.normalize();
	offset_sec.normalize();
	offset_thi.normalize();

	Vec2 attackVec_fir = offset_fir * 75 * static_cast<int>(_shotRange); 
	Vec2 attackVec_sec = offset_sec * 75 * static_cast<int>(_shotRange);
	Vec2 attackVec_thi = offset_thi * 75 * static_cast<int>(_shotRange);

	std::vector<Vec2> attackVec;
	attackVec.push_back(attackVec_fir);
	attackVec.push_back(attackVec_sec);
	attackVec.push_back(attackVec_thi);
	Bullet* bullet[3];

	//add projectile
	for (auto i = 0; i < 3; ++i)
	{
		bullet[i] = BulletFactory::getInstance()->createWithClassID("BurningBullet");
		if (bullet[i] == nullptr)
			problemLoading("BurningBullet");
		bullet[i]->setHitPoint(this->getHitPoint());
		bullet[i]->setEnergy(_maxEnergy / 3 + 1);
		bullet[i]->setParentHero(this);
		bullet[i]->setPosition(this->getPosition());
		this->getParent()->addChild(bullet[i]);

		//create the animation
		auto shot = MoveBy::create(1.0, attackVec[i]);
		auto removeBullet = RemoveSelf::create();
		bullet[i]->runAction(Sequence::create(shot, removeBullet, nullptr));

	}

	return true;
}

bool  Xueli::skillAnimation(cocos2d::Point touchLocation)
{
	/** the animation of skill */
	//convert the location to offset

	Vec2 offset_fir = touchLocation - this->getPosition();
	Vec2 offset_sec = Vec2(touchLocation.x, touchLocation.y + 50.0f) - this->getPosition();
	Vec2 offset_thi = Vec2(touchLocation.x, touchLocation.y - 50.0f) - this->getPosition();

	//get the vector of attack according to the range of hero

	offset_fir.normalize();
	offset_sec.normalize();
	offset_thi.normalize();

	Vec2 attackVec_fir = offset_fir * 75 * static_cast<int>(_shotRange); 
	Vec2 attackVec_sec = offset_sec * 75 * static_cast<int>(_shotRange);
	Vec2 attackVec_thi = offset_thi * 75 * static_cast<int>(_shotRange);

	std::vector<Vec2> attackVec;
	attackVec.push_back(attackVec_fir);
	attackVec.push_back(attackVec_sec);
	attackVec.push_back(attackVec_thi);

	Bullet* bullet[2];
	
	std::string bulletNo[6] = { "1","2","3","4","5","6" };
	int count = 1;
	

	//add projectile
	for (auto i = 0; i < 2; ++i)
	{
		bullet[i] = BulletFactory::getInstance()->createWithClassID("BurningBullet");
		if (bullet[i] == nullptr)
			problemLoading("BurningBullet");
		bullet[i]->setHitPoint(this->getSkillHitPoint());
		bullet[i]->setEffect(Bullet::Effect::NONE);
		bullet[i]->setParentHero(this);
		this->getParent()->addChild(bullet[i]);
		bullet[i]->setVisible(false);
		this->scheduleOnce(
			[=](float fdelta)
			{
				bullet[i]->setPosition(this->getPosition());
				bullet[i]->setVisible(true);

				auto shot = MoveBy::create(static_cast<float>(_shotRange) / 3, attackVec[0]);
				auto removeBullet = RemoveSelf::create();
				bullet[i]->runAction(Sequence::create(shot, removeBullet, nullptr));
			}
		, 0.2 * count, bulletNo[i]);

		++count;
	}
	count = 1;
	for (auto i = 0; i < 2; ++i)
	{
		bullet[i] = BulletFactory::getInstance()->createWithClassID("BurningBullet");
		if (bullet[i] == nullptr)
			problemLoading("BurningBullet");
		bullet[i]->setHitPoint(this->getSkillHitPoint());
		bullet[i]->setEffect(Bullet::Effect::NONE);
		bullet[i]->setParentHero(this);
		this->getParent()->addChild(bullet[i]);
		bullet[i]->setVisible(false);
		this->scheduleOnce(
			[=](float fdelta)
			{
				bullet[i]->setPosition(this->getPosition());
				bullet[i]->setVisible(true);

				auto shot = MoveBy::create(static_cast<float>(_shotRange) / 3, attackVec[1]);
				auto removeBullet = RemoveSelf::create();
				bullet[i]->runAction(Sequence::create(shot, removeBullet, nullptr));
			}
		, 0.2 * count, bulletNo[i + 2]);

		++count;
	}
	count = 1;

	for (auto i = 0; i < 2; ++i)
	{
		bullet[i] = BulletFactory::getInstance()->createWithClassID("BurningBullet");
		if (bullet[i] == nullptr)
			problemLoading("BurningBullet");
		bullet[i]->setHitPoint(this->getSkillHitPoint());
		bullet[i]->setEffect(Bullet::Effect::NONE);
		bullet[i]->setParentHero(this);
		this->getParent()->addChild(bullet[i]);
		bullet[i]->setVisible(false);
		this->scheduleOnce(
			[=](float fdelta)
			{
				bullet[i]->setPosition(this->getPosition());
				bullet[i]->setVisible(true);

				auto shot = MoveBy::create(static_cast<float>(_shotRange) / 3, attackVec[2]);
				auto removeBullet = RemoveSelf::create();
				bullet[i]->runAction(Sequence::create(shot, removeBullet, nullptr));
			}
		, 0.2 * count, bulletNo[i + 4]);

		++count;
	}
	
	return true;
}