/** @author Ê±ÌìÒÝ */

#include "Participant/RobotParticipant.h"

USING_NS_CC;

std::default_random_engine Robot::_robotRand;
bool Robot::_initRand = false;

Robot* Robot::create()
{
    return Robot::createWithHeroID("Beiya");
}

Robot* Robot::createWithHeroID(std::string HeroID)
{
    Robot* robot = new(std::nothrow) Robot();
    if (robot)
    {
        robot->autorelease();

        robot->setHeroType(HeroID);

        if (!_initRand) {
            _robotRand.seed(time(0));
            _initRand = true;
        }

        return robot;
    }
    else
    {
        delete robot;
        robot = nullptr;
        return nullptr;
    }
}

Robot::Robot()
{
    this->Node::setPosition(0, 0);
    this->setName("robot");
    this->schedule(SEL_SCHEDULE(&Robot::autoMove));
    this->schedule(SEL_SCHEDULE(&Robot::autoAttack));
}

void Robot::autoMove(float fdelta)
{
    USING_NS_CC;

    //get hero information
    auto heroPos = _hero->getPosition();
    int shotRange = _hero->getShotRange();

    static Node* moveTarget = nullptr;
//    static Node randTarget;

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
                else {
//                    std::uniform_real_distribution<double> u(-1, 1);
//                    float x = heroPos.x + u(_robotRand);
//                    float y = heroPos.y + u(_robotRand);
//                    randTarget.setPosition(x, y);
//                    moveTarget = &randTarget;
                }

                return true;
            }),
        Rect(heroPos.x - shotRange, heroPos.y - shotRange, 2 * shotRange, 2 * shotRange), nullptr);

    //move robot
    if (moveTarget->getPosition()!=_hero->getPosition()) {
        _hero->moveStep(moveTarget->getPosition());
    }
    else {
//        this->unschedule(SEL_SCHEDULE(&Robot::autoMove));
//        std::uniform_real_distribution<double> u(-10, 10);
//        float x = heroPos.x + u(_robotRand);
//        float y = heroPos.y + u(_robotRand);
//        Point randTarget(x, y);
//        this->schedule([=](float fdelta = 1)
//            {
//                _hero->moveStep(randTarget);
//
//               if (_hero->getPosition() == randTarget) {
//                    this->unschedule("random move");
//                    this->schedule(SEL_SCHEDULE(&Robot::autoMove));
//                }
//            }
//        , "random move");
//        _hero->moveStep(x, y);
    }
}

void Robot::autoAttack(float fdelta)
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
                if (queryNode->getName() == "hero") hero = queryNode->getParent();
                if (queryNode->getName() == "box")  box = queryNode;

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