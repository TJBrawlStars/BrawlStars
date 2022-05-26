//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

/**
* @class Robot
* @brief use the class as a given kind of hero
* @details give the type of robot when creating it
*          the robot will automatically move and attack
*/
template<typename HeroType>
class Robot :public Node
{
public:
    /**
    */
    static Robot* createRobot();

    virtual void setPosition(const cocos2d::Vec2& position) { return _robot->setPosition(position); }
    virtual void setPosition(float x, float y) { return _robot->setPosition(x, y); }
    virtual const cocos2d::Vec2& getPosition() const { return _robot->getPosition(); }

    void setAutoMove(bool state)   noexcept = delete;
    void setAutoAttack(bool state) noexcept = delete;

protected:
    HeroType* _robot;

private:
    Robot();

    /** schedule selectors */
    void autoMove(float fdelta = 1);
    void autoAttack(float fdelta = 1);
};

template<typename HeroType>
Robot<HeroType>* Robot<HeroType>::createRobot()
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
    _robot = HeroType::create();
    this->setPosition(0, 0);
    this->addChild(_robot);
    this->setName("robot");
    this->schedule(SEL_SCHEDULE(&Robot::autoMove));
    this->schedule(SEL_SCHEDULE(&Robot::autoAttack));

    _robot->setDiamond(5);
}

template<typename HeroType>
void Robot<HeroType>::autoMove(float fdelta)
{
    USING_NS_CC;

    //get hero information
    auto heroPos = _robot->getPosition();
    int shotRange = _robot->getShotRange();

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
                }
                else if (box) {
                    moveTarget = box;
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);

    //move robot
    if (moveTarget) {
        _robot->moveStep(moveTarget->getPosition());
    }
    else {

    }
}

template<typename HeroType>
void Robot<HeroType>::autoAttack(float fdelta)
{
    USING_NS_CC;

    //get hero information
    auto heroPos = _robot->getPosition();
    int shotRange = _robot->getShotRange();

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
                    if (_robot != hero&&dynamic_cast<Hero*>(hero)->alive()) {
                        if (_robot->skillStatus())
                            _robot->releaseSkill(hero->getPosition());
                        else
                            _robot->attack(hero->getPosition());
                    }
                }
                else if (box) {
                    _robot->attack(box->getParent()->getPosition());
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);
}