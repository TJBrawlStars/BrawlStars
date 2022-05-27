//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Participant/ParticipantNode.hpp"

/**
* @class Robot
* @brief derived from Participant and use template parameter to create hero
* @details the robot will automatically move and attack
*/
template<typename HeroType>
class Robot :public Participant
{
public:
    /**
    */
    static Robot* create();

    void setAutoMove(bool state)   noexcept = delete;
    void setAutoAttack(bool state) noexcept = delete;

private:
    Robot();

    /** schedule selectors */
    void autoMove(float fdelta = 1);
    void autoAttack(float fdelta = 1);
};

template<typename HeroType>
Robot<HeroType>* Robot<HeroType>::create()
{
    Robot* robot = new(std::nothrow) Robot();
    if (robot)
    {
        robot->autorelease();

        return robot;
    }
    else
    {
        delete robot;
        robot = nullptr;
        return nullptr;
    }
}

template<typename HeroType>
Robot<HeroType>::Robot()
{
    _hero = HeroType::create();
    this->setParticipant();
    this->setName("robot");
    this->schedule(SEL_SCHEDULE(&Robot::autoMove));
    this->schedule(SEL_SCHEDULE(&Robot::autoAttack));
}

template<typename HeroType>
void Robot<HeroType>::autoMove(float fdelta)
{
    USING_NS_CC;

    //get hero information
    auto heroPos = _hero->getPosition();
    int shotRange = _hero->getShotRange();

    static Node* moveTarget = nullptr;

    //query and get the target
    dynamic_cast<Scene*>(this->getParent())->getPhysicsWorld()->queryRect(
        PhysicsQueryRectCallbackFunc([=](PhysicsWorld& world, PhysicsShape& shape, void* data)->bool
            {
                //recognize the node
                typedef Node* NodePtr;
                NodePtr hero = nullptr, box = nullptr, diamond = nullptr;
                NodePtr queryNode = shape.getBody()->getNode();
                if (queryNode->getName() == "hero")    hero = queryNode;
                if (queryNode->getName() == "box")     box = queryNode;
                if (queryNode->getName() == "diamond") diamond = queryNode;
                
                //callbacks
                if (diamond) {
                    moveTarget = diamond;

                    return true;
                }
                else if (hero) {
                    if (moveTarget && moveTarget->getName() == "diamond")
                        return true;

                    moveTarget = hero;
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);

    //move robot
    if (moveTarget) {
        _hero->moveStep(moveTarget->getPosition());
    }
    else {

    }
}

template<typename HeroType>
void Robot<HeroType>::autoAttack(float fdelta)
{
    USING_NS_CC;

    //get hero information
    auto heroPos = _hero->getPosition();
    int shotRange = _hero->getShotRange();

    //query
    dynamic_cast<Scene*>(this->getParent())->getPhysicsWorld()->queryRect(
        PhysicsQueryRectCallbackFunc([=](PhysicsWorld& world, PhysicsShape& shape, void* data)->bool
            {
                //recognize the node
                typedef Node* NodePtr;
                NodePtr hero = nullptr, box = nullptr;
                NodePtr queryNode = shape.getBody()->getNode();
                if (queryNode->getName() == "hero") hero = queryNode;
                if (queryNode->getName() == "box") box = queryNode;

                //callbacks
                if (hero) {
                    if (_hero != hero && dynamic_cast<Hero*>(hero)->alive()) {
                        if (_hero->skillStatus())
                            _hero->releaseSkill(hero->getPosition());
                        else
                            _hero->attack(hero->getPosition());
                    }
                }
                else if (box) {
                    _hero->attack(box->getParent()->getPosition());
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);
}