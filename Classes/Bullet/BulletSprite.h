//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

class Hero;

/**
* @class Bullet
* @brief bullets of hero
* @details Bullet is the child of game scene
*/
class Bullet :public cocos2d::Sprite
{
	friend class BulletFactory;

public:
	enum class Effect {
		NONE,
		FREEZE,
		BURN,
		RECOVER
	};

	/// @name Attribute Manipulators
	/// @{

	int getHitPoint()      const noexcept { return _hitPoint; }
	double getEnergy()     const noexcept { return _energy; }
	Effect getEffect()     const noexcept { return _effect; }
	Hero* getParentHero()  const noexcept { return _parentHero; }

	void setExist(bool exist)                   noexcept;
	void setHitPoint(int hitPoint)              noexcept { _hitPoint = hitPoint; }
	void setEnergy(double energy)               noexcept { _energy = energy; }
	void setEffect(Effect effect)               noexcept { _effect = effect; }
	void setParentHero(Hero* parent)            noexcept { _parentHero = parent; }
	void setBulletTecture(std::string filepath) noexcept { _bulletPicture = filepath; }

	/// @}
	/// end of Attribute Manipulators

protected:
	/** Bullet Attributes */
	int _hitPoint = 0;              ///< the hit point of the bullet which is related to hero
	double _energy = 0;             ///< the energy of each bullet
	Effect _effect = Effect::NONE;  ///< the special effect of bullet

	/** derived classes override the effect of the bullet */
	virtual void effectOnHero(Hero* hero) {}
	virtual void effectOnWall(cocos2d::Sprite* wall) {}
	virtual void effectAnimation() {}

private:
	/** Initializers */
	bool initWithFile(const std::string& filename);
	void initializeBulletPhysics();

	Hero* _parentHero = nullptr;    ///< the parent hero of the bullet
	std::string _bulletPicture;     ///< file path of the bullet picture

	/** Contact Event */
	cocos2d::EventListenerPhysicsContact* _contactListener = nullptr;
	bool _initContactListener = false;
	void initializeContactListener();
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeperate(cocos2d::PhysicsContact& contact);
};