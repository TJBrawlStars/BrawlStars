//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

/**
* @class Beiya
* @brief the class is derived from hero with detailed attributes
* @details the attributes of Beiya
*		_maxHealthPoint = 3360;
*		_maxAmmo = 1;
*		_hitPoint = 1120;
*		_moveSpeed = Level::MEDIUM;
*		_shotRange = Level::HIGH;
*		_loadSpeed = Level::EXTREME_HIGH;
*/
class Beiya :public Hero {
public:
	/**
	* @fn createBeiya
	* @brief the only way to instantiate class Beiya
	* @warning the create function with filename is disabled
	*/
	static Beiya* createBeiya();

protected:
	/**
	* @fn attack
	* @brief the attack callback of Beiya
	*/
	virtual bool attack(cocos2d::Touch* touch, cocos2d::Event* event) override;

private:
	/** the initialization of Beiya */
	Beiya();
	CREATE_FUNC(Beiya)
	static Beiya* create(const std::string&) = delete;
	bool init();

	static const std::string _beiyaPicture;  ///< The filename of the picture
};