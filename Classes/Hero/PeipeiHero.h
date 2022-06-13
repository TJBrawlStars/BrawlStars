//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Bullet/BulletSprite.h"

/**
* @class Peipei
* @brief the class is derived from hero with detailed attributes
* @details the attributes of Peipei
*		_maxHealthPoint = 3360;
*		_hitPoint = 1120;
*		_maxAmmo = 1;
*		_moveSpeed = Level::MEDIUM;
*		_shotRange = Level::HIGH;
*		_loadSpeed = Level::EXTREME_HIGH;
*/
class Peipei :public Hero
{
	friend class HeroRegister;

public:
	/**
	* @fn create
	* @brief to register the constructor to the factory
	*/
	static Peipei* create();

protected:
	/** overrides */
	virtual bool attackAnimation(cocos2d::Point touchLocation) override;
	virtual bool skillAnimation(cocos2d::Point touchLocation)  override;

private:
	/** the initialization of Beiya */
	Peipei();
};