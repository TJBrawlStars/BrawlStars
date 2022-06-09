//’≈æ∏ø≠ 2151396
#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Bullet/BulletSprite.h"

/**
* @class ABo
* @brief the class is derived from hero with detailed attributes
* @details the attributes of ABo
*		_maxHealthPoint = 3600;
*		_hitPoint = 600;
*		_maxAmmo = 1;
*		_moveSpeed = Level::MEDIUM;
*		_shotRange = Level::HIGH;
*		_loadSpeed = Level::HIGH;
*/

class ABo :public Hero
{

	friend class HeroRegister;

public:
	/**
	* @fn create
	* @brief to register the constructor to the factory
	*/
	static ABo* create();

protected:
	/** overrides */
	virtual bool attackAnimation(cocos2d::Point touchLocation) override;
	virtual bool skillAnimation(cocos2d::Point touchLocation)  override;

private:
	/** the initialization of ABo */
	ABo();
};
