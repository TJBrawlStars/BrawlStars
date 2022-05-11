//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Hero/BulletSprite.h"
#include <functional>
#include <map>

/**
* @class Hero
* @brief Hero is the base class of the heroes in Brawl Stars
*/
class Hero :public cocos2d::Sprite {
public:
	/**
	* @enum Level
	* @brief Level can describe an attribute of the hero
	*/
	enum class Level :char {
		ZERO = 0,
		EXTREME_LOW = 1,
		LOW = 2,
		MEDIUM = 3,
		HIGH = 4,
		EXTREME_HIGH = 5
	};

	/// @name Listener Set-ups
	/// @{

	/**
	* @fn setKeyboardListener
	* @brief choose whether to use the keyboard to move hero. The function is disabled by default
	*/
	void setKeyboardListener(bool keyboardState) noexcept;

	/**
	* @fn setTouchListener
	* @brief choose whether to use the mouse to shot. The function is disabled by default
	*/
	void setTouchListener(bool touchState) noexcept;

	/**
	* @fn setContactListener
	* @brief choose whether to allow physics contact. The function is disabled by default
	*/
	void setContactListener(bool contactState) noexcept;

	/// @}
	/// end of Listener Set-ups

	/**
	* @fn getMoveSpeed
	* @return the speed of hero(the distance the hero moves every second)
	*/
	float getMoveSpeed() const noexcept { return static_cast<float>(_moveSpeed); }

	int getHitPoint()    const noexcept { return _hitPoint; }

	int getHP()          const noexcept { return _healthPoint; }

	/// @name HP Manipuators
	/// @{

	/**
	* @fn increaseHP
	* @brief increase HP and update the blood strip
	* @param increasePoint the hp increasement point
	* @return the HP after increasing
	* @exception out_of_range the increasement point is negative
	*/
	int increaseHP(const int increasePoint);

	/**
	* @fn deductHP
	* @brief deduct hp and update the blood strip
	* @param deductPoint the hp deduction point
	* @exception out_of_range the deduction point is negative
	*/
	int deductHP(const int deductPoint);

	int setHP(const int HP) = delete;

	/// @}
	/// end of HP Manipulators

protected:
	/**
	* @brief the constructor is used to initialize the constant variables
	* @details derived classes must give the constant parameters, so the default constructor is deleted
	*/
	Hero(const int maxHealthPoint, const int maxAmmo);
	Hero() = delete;

	/** the attributes of a hero */
	const int _maxHealthPoint;
	const int _maxAmmo;
	int _healthPoint;
	int _hitPoint;
	int _ammo;
	int _energy = 0;
	int _diamond = 0;
	Level _shotRange;
	Level _moveSpeed;
	Level _loadSpeed;
	
	/**
	* @fn attack
	* @brief derived classes need to override the attack function, which will act as the listener callback
	*/
	virtual bool attack(cocos2d::Touch* touch, cocos2d::Event* event) = 0;

	/**
	* @fn startLoading
	* @brief each bullet is loaded for 0.75 seconds
	*/
	void startLoading(float fdelta = 1);

	/**
	* @fn initializeHeroPhysics
	* @brief initialize with hero's physics body
	* @warning the function should be used after the set of hero's texture
	*/
	void initializeHeroPhysics(Hero* hero);

	/**
	* @fn initializeBulletPhysics
	* @brief initialize with bullet's physics body
	*/
	void initializeBulletPhysics(Bullet* bullet);

	/**
	* @fn initializeBloodStrip
	* @brief draw the blood strip
	* @warning the function should be used after the set of hero's texture
	*/
	void initialzeBloodStrip(const int maxHealthPoint);

	/**
	* @fn initializeAmmoStrip
	* @brief draw the ammo strip
	* @warning the function should be used after the set of hero's texture
	*/
	void initializeAmmoStrip(const int maxAmmo);

private:
	cocos2d::ui::LoadingBar* _bloodStrip = cocos2d::ui::LoadingBar::create("bloodStrip.png");  ///< the blood strip
	cocos2d::Sprite* _ammoStrip[3];
	std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyCodeState;  ///< control the state of keys

	/** event listeners */
	cocos2d::EventListenerKeyboard* _keyboardListener;
	cocos2d::EventListenerTouchOneByOne* _touchListener;
	cocos2d::EventListenerPhysicsContact* _contactListener;

	/** initializer of the event listeners */
	void initializeKeyboardListener();
	void initializeTouchListener();
	void initializeContactListener();

	/** callback functions of the event listeners */
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*) { _keyCodeState[keyCode] = true; }
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*) { _keyCodeState[keyCode] = false; }
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return this->attack(touch, event); }
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	/**
	* @fn moveHero
	* @brief used by scheduler to move hero
	*/
	void moveHero(float fdelta = 1);
};