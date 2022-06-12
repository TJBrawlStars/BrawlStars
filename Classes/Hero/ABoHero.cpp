//张靖凯 2151396
#include "Hero/ABoHero.h"
#include "Factory/HeroFactory.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace 
{
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
	}

	HeroRegister registerCreator(std::string("ABo"), HeroCreator(ABo::create));
}

ABo* ABo::create()
{
	return new(std::nothrow) ABo();
}

ABo::ABo() :Hero(3600, 1, Level::MEDIUM)
{
	_ammo = _maxAmmo;
	_hitPoint = 600;
	_skillHitPoint = 800;
	_shotRange = Level::EXTREME_HIGH;
	_loadSpeed = Level::HIGH;

	this->setHeroTexture("HeroResource/LiPlane.png");
}

bool ABo::attackAnimation(cocos2d::Point touchLocation)
{
	/** the animation of attack */
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();

	//add projectile
	auto projectile = BulletFactory::getInstance()->createWithClassID("ArrowBullet");
	if (projectile == nullptr)
		problemLoading("ArrowBullet");
	projectile->setHitPoint(this->getHitPoint());
	projectile->setEnergy(_maxEnergy / 3 + 1);
	projectile->setParentHero(this);
	projectile->setPosition(this->getPosition());
	this->getParent()->addChild(projectile);

	//箭头调整角度
	double len_y = touchLocation.y - this->getPosition().y;
	double len_x = touchLocation.x - this->getPosition().x;

	double tan_yx = tan_yx = abs(len_y) / abs(len_x);
	float angle = 0;
	if (len_y > 0 && len_x < 0) {
		angle = atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y > 0 && len_x > 0) {
		angle = 90 - atan(tan_yx) * 180 / M_PI;
	}
	else if (len_y < 0 && len_x < 0) {
		angle = -atan(tan_yx) * 180 / M_PI - 90;
	}
	else if (len_y < 0 && len_x > 0) {
		angle = atan(tan_yx) * 180 / M_PI + 90;
	}
	projectile->setRotation(angle-90);

	//get the vector of attack according to the range of hero
	offset.normalize();
	Vec2 attackVec = offset * 75 * static_cast<int>(_shotRange);

	//create the animation
	auto shot = MoveBy::create(0.7, attackVec);
	auto removeBullet = RemoveSelf::create();
	projectile->runAction(Sequence::create(shot, removeBullet, nullptr));


	return true;
}

bool ABo::skillAnimation(cocos2d::Point touchLocation)
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
		i = BulletFactory::getInstance()->createWithClassID("ABoBig");
		if (i == nullptr)
			problemLoading("ABoBig");
		i->setHitPoint(this->getSkillHitPoint());
		i->setEffect(Bullet::Effect::BURN);
		i->setParentHero(this);
		this->getParent()->addChild(i);
		i->setVisible(false);
		this->scheduleOnce(
			[=](float fdelta)
			{
				i->setPosition(this->getPosition());
				i->setVisible(true);
				Vec2 attackVec = (offset + Vec2(cocos2d::random(-0.05f, 0.05f), cocos2d::random(-0.05f, 0.05f))) * 75 * static_cast<int>(_shotRange);
				
				//箭头调整角度
				double len_y = touchLocation.y - this->getPosition().y;
				double len_x = touchLocation.x - this->getPosition().x;

				double tan_yx = tan_yx = abs(len_y) / abs(len_x);
				float angle = 0;
				if (len_y > 0 && len_x < 0) {
					angle = atan(tan_yx) * 180 / M_PI - 90;
				}
				else if (len_y > 0 && len_x > 0) {
					angle = 90 - atan(tan_yx) * 180 / M_PI;
				}
				else if (len_y < 0 && len_x < 0) {
					angle = -atan(tan_yx) * 180 / M_PI - 90;
				}
				else if (len_y < 0 && len_x > 0) {
					angle = atan(tan_yx) * 180 / M_PI + 90;
				}
				i->setRotation(angle - 90);
				
				auto shot = MoveBy::create(0.8f, attackVec);
				auto removeBullet = RemoveSelf::create();
				i->runAction(Sequence::create(shot, removeBullet, nullptr));
			}
		, 0.1f * count, bulletNo[count - 1]);

		count++;
	}

	return true;
}