/** @author Ê±ÌìÒÝ*/

#include "Participant/PlayerParticipant.h"

USING_NS_CC;

Player* Player::create()
{
    return Player::createWithHeroID("Beiya");
}

Player* Player::createWithHeroID(std::string heroID)
{
    Player* player = new(std::nothrow) Player();
    if (player)
    {
        player->autorelease();

        player->setHeroType(heroID);

        return player;
    }
    else
    {
        delete player;
        player = nullptr;
        return nullptr;
    }
}

Player::Player()
{
    this->Node::setPosition(0, 0);
    this->setName("player");
    this->initializeKeyboardListener();
    this->initializeTouchListener();
}

void Player::setKeyboardListener(bool keyboardState) noexcept
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

void Player::setTouchListener(bool touchState) noexcept
{
    //judge whether the touch state needs to be reset
    if (_touchListener->isEnabled() == touchState)
        return;
    else
        _touchListener->setEnabled(touchState);
}

void Player::initializeKeyboardListener()
{
    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
    _keyboardListener->setEnabled(false);
}

void Player::initializeTouchListener()
{
    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _touchListener->setEnabled(false);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
    _keyCodeState[keyCode] = true;
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
    _keyCodeState[keyCode] = false;

    if (_hero->skillStatus() && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_F) {
        _hero->prepareSkillRelease();
        _releaseSkill = !_releaseSkill;
    }
}

bool Player::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //get the location of touch point
    cocos2d::Point touchLocation = this->getParent()->convertToNodeSpace(touch->getLocation());

    //callback functions
    if (!_releaseSkill) {
        return _hero->attack(touchLocation);
    }
    else {
        _releaseSkill = false;
        return _hero->releaseSkill(touchLocation);
    }
}

void Player::moveHero(float fdelta) noexcept
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