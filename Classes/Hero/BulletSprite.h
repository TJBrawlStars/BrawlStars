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
class Bullet :public cocos2d::Sprite {
public:
	enum class Effect { NONE, FREEZE, BURN };

	static Bullet* createBullet(const std::string& filename);

	int hitPoint()  const noexcept { return _hitPoint; }
	Effect effect() const noexcept { return _effect; }
	Hero* parentHero()  const noexcept { return _parentHero; }

	void sethitPoint(int hitPoint) noexcept { _hitPoint = hitPoint; }
	void setEffect(Effect effect)  noexcept { _effect = effect; }
	void setParentHero(Hero* parent)   noexcept { _parentHero = parent; }

private:
	bool initWithFile(const std::string& filename);
	CREATE_FUNC(Bullet)

	Hero* _parentHero = nullptr;    ///< the parent hero of the bullet
	int _hitPoint = 0;              ///< the hit point of the bullet which is related to hero
	Effect _effect = Effect::NONE;  ///< the special effect of bullet
	std::string _bulletPicture;     ///< the picture of bullet

	/**
	* @fn initializeBulletPhysics
	* @brief initialize with bullet's physics body
	*/
	void initializeBulletPhysics();
};