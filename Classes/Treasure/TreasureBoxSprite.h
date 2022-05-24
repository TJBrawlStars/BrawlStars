//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <random>

#define CLASS_DECLARATION_ACCESS public

/**
* @class TreasureBox
* @brief contain a box and a diamond, diamond will be automatically generated when the box disappear
*/
class TreasureBox :public cocos2d::Sprite
{
CLASS_DECLARATION_ACCESS:
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

		void setExist(bool exist);

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

	/**
	* @class Diamond
	* @brief a member of treasure box
	*/
	class Diamond :public cocos2d::Sprite
	{
	public:
		static Diamond* createDiamond();

		/**
		* @fn dropDiamond
		* @brief drop a diamond close to the point
		* @details the position of the diamond is automatically set
		* @warning dont modify the position of the diamond
		*/
		static Diamond* dropDiamond(cocos2d::Point dropPoint);

		void setExist(bool exist);

	private:
		Diamond() {}
		bool initWithFile(const std::string& filename);
		void initializeDiamondPhysics();

		static std::default_random_engine _diamondRand;
		static bool _initRand;
	};

public:
	/** create an object */
	static TreasureBox* createTreasureBox();

	Box* getBox()         const noexcept { return _box; }
	Diamond* getDiamond() const noexcept { return  _diamond; }

private:
	/** the initializers */
	TreasureBox();
	CREATE_FUNC(TreasureBox)

	Box* _box;
	Diamond* _diamond;
};