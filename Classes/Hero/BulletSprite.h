//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

class Hero;

/**
* @class Bullet
* @brief bullets of hero
* @details Bullet is the child of Hero's parent node
*/
class Bullet :public cocos2d::Sprite
{
public:
	enum class Effect { NONE, FREEZE, BURN };

	static Bullet* createBullet(const std::string& filename);

	int getHitPoint()      const noexcept { return _hitPoint; }
	double getEnergy()     const noexcept { return _energy; }
	Effect getEffect()     const noexcept { return _effect; }
	Hero* getParentHero()  const noexcept { return _parentHero; }

	void setHitPoint(int hitPoint)    noexcept { _hitPoint = hitPoint; }
	void setEnergy(double energy)     noexcept { _energy = energy; }
	void setEffect(Effect effect)     noexcept { _effect = effect; }
	void setParentHero(Hero* parent)  noexcept { _parentHero = parent; }

private:
	bool initWithFile(const std::string& filename);
	void initializeBulletPhysics();

	Hero* _parentHero = nullptr;    ///< the parent hero of the bullet
	int _hitPoint = 0;              ///< the hit point of the bullet which is related to hero
	double _energy = 0;             ///< the energy of each bullet
	Effect _effect = Effect::NONE;  ///< the special effect of bullet
	std::string _bulletPicture;     ///< the picture of bullet
};