//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Treasure/DiamondSprite.h"

/**
* @class Box
* @brief the box of treasure, a member of treasure box
*/
class Box :public cocos2d::Sprite
{
public:
	static Box* createBox();

	/**
	* @fn deductHP
	* @brief deduct hp and update the blood strip. generate diamond if the blood strip is empty
	* @param deductPoint the hp deduction point
	* @exception out_of_range the deduction point is negative
	*/
	int deductHP(const int deductPoint);

	int getHP() const noexcept { return _healthPoint; }

private:
	/** the initializers */
	Box() :_healthPoint(_maxHealthPoint) {}
	bool initWithFile(const std::string& filename);
	void initializeBoxPhysics();
	void initializeBloodStrip(const int maxHealthPoint);

	/** the attributes */
	const int _maxHealthPoint = 6000;
	int _healthPoint;
	cocos2d::ui::LoadingBar* _bloodStrip = cocos2d::ui::LoadingBar::create("bloodStrip.png");  ///< the blood strip
};