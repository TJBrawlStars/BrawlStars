//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

template<typename HeroType>
class Robot :public cocos2d::Node
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
    this->schedule(SEL_SCHEDULE(&Robot::autoMove));
    this->schedule(SEL_SCHEDULE(&Robot::autoAttack));
}

template<typename HeroType>
void Robot<HeroType>::autoMove(float fdelta)
{

}

template<typename HeroType>
void Robot<HeroType>::autoAttack(float fdelta)
{
    USING_NS_CC;
    auto heroPos = _robot->getPosition();
    int shotRange = _robot->getShotRange();
    dynamic_cast<Scene*>(this->getParent())->getPhysicsWorld()->queryRect(
        PhysicsQueryRectCallbackFunc([=](PhysicsWorld& world, PhysicsShape& shape, void* data)->bool
            {
                //recognize the node
                typedef Node* NodePtr;
                NodePtr hero = nullptr;
                NodePtr queryNode = shape.getBody()->getNode();
                if (queryNode->getName() == "hero")hero = queryNode;

                if (hero) {
                    if (_robot != hero&&dynamic_cast<Hero*>(hero)->alive()) {
                        if (_robot->skillStatus())
                            _robot->releaseSkill(hero->getPosition());
                        else
                            _robot->attack(hero->getPosition());
                    }
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);
}