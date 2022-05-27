//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Participant/ParticipantNode.hpp"
#include <map>

/**
* @class Player
* @brief derived from Participant and use template parameter to create hero
* @details the hero can be controled by mouse and keyboard
*/
template<typename HeroType>
class Player :public Participant
{
public:
	static Player* create();
    static Player* createWithHeroID(std::string heroid) = delete;

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

template<typename HeroType>
Player<HeroType>* Player<HeroType>::create()
{
    Player* player = new(std::nothrow) Player();
    if (player)
    {
        player->autorelease();

        return player;
    }
    else
    {
        delete player;
        player = nullptr;
        return nullptr;
    }
}

template<typename HeroType>
Player<HeroType>::Player()
{
    _hero = HeroType::create();
    this->Node::setPosition(0, 0);
    this->addChild(_hero);
    this->setName("player");
    this->initializeKeyboardListener();
    this->initializeTouchListener();

    if (_keyCodeState[cocos2d::EventKeyboard::KeyCode::KEY_W] == true)
        log("test map");
}

template<typename HeroType>
void Player<HeroType>::setKeyboardListener(bool keyboardState) noexcept
{
    //judge whether the keyboard state needs to be reset
    if (_keyboardListener->isEnabled() == keyboardState)
        return;

    //set the state of keyboardlistener and scheduler
    if (keyboardState) {
        _keyboardListener->setEnabled(true);
        this->schedule(SEL_SCHEDULE(&Player::moveHero));
    }
    else {
        _keyboardListener->setEnabled(false);
        this->unschedule(SEL_SCHEDULE(&Player::moveHero));
    }
}

template<typename HeroType>
void Player<HeroType>::setTouchListener(bool touchState) noexcept
{
    //judge whether the touch state needs to be reset
    if (_touchListener->isEnabled() == touchState)
        return;
    else
        _touchListener->setEnabled(touchState);
}

template<typename HeroType>
void Player<HeroType>::initializeKeyboardListener()
{
    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
    _keyboardListener->setEnabled(false);
}

template<typename HeroType>
void Player<HeroType>::initializeTouchListener()
{
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);
}

template<typename HeroType>
void Player<HeroType>::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
    _keyCodeState[keyCode] = true;
}

template<typename HeroType>
void Player<HeroType>::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
    _keyCodeState[keyCode] = false;

    if (_hero->skillStatus() && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_F) {
        _hero->prepareSkillRelease();
        _releaseSkill = !_releaseSkill;
    }
}

template<typename HeroType>
bool Player<HeroType>::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //get the location of touch point
    cocos2d::Point touchLocation = dynamic_cast<Scene*>(this->getParent())->convertToNodeSpace(touch->getLocation());

    //callback functions
    if (!_releaseSkill) {
        return _hero->attack(touchLocation);
    }
    else {
        _releaseSkill = false;
        return _hero->releaseSkill(touchLocation);
    }
}

template<typename HeroType>
void Player<HeroType>::moveHero(float fdelta) noexcept
{
    using Code = cocos2d::EventKeyboard::KeyCode;

    //record the offset of coordinate
    int offsetX = 0, offsetY = 0;
    if (_keyCodeState[Code::KEY_W] == true)
        offsetY = 1;
    else if (_keyCodeState[Code::KEY_S] == true)
        offsetY = -1;
    if (_keyCodeState[Code::KEY_A] == true)
        offsetX = -1;
    else if (_keyCodeState[Code::KEY_D] == true)
        offsetX = 1;

    //move hero
    Vec2 offset = Vec2(offsetX, offsetY);
    Point target = _hero->getPosition() + offset;
    _hero->moveStep(target);
}