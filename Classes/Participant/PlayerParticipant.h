/** @author  ±ÃÏ“› */

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Participant/ParticipantNode.h"
#include <map>

/**
* @class Player
* @brief derived from Participant and use template parameter to create hero
* @details the hero can be controled by mouse and keyboard
*/
class Player :public Participant
{
public:
    static Player* create();
    static Player* createWithHeroID(std::string heroid);

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
    * @fn moveHero
    * @brief used by scheduler to move hero with keyboard listener
    */
    void moveHero(float fdelta = 1) noexcept;

private:
    Player();

    bool _releaseSkill = false;                                     ///< control whether to release skill
    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyCodeState;  ///< control the state of keys

    /** event listeners */
    cocos2d::EventListenerKeyboard* _keyboardListener;
    cocos2d::EventListenerTouchOneByOne* _touchListener;

    /** initializer of the event listeners */
    void initializeKeyboardListener();
    void initializeTouchListener();

    /** callback functions of the event listeners */
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};