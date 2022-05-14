/**
* @author 张靖凯
* @brief 初始化障碍物
*/
#include"cocos2d.h"
#include "View\GameScene.h"
#include "Const/Const.h"
using namespace std;
USING_NS_CC;

void GameScene::addBarrier()
{
    auto group = _mapinfo._map->getObjectGroup("barrier");
    ValueVector barrierObjects = group->getObjects();
    for (auto barrier : barrierObjects)
    {
        ValueMap& dict = barrier.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        PhysicsBody* tmpPhysicsBody = PhysicsBody::createBox(Size(width, height),
            PhysicsMaterial(100.0f, 0.0f, 0.0f));
        tmpPhysicsBody->setDynamic(false);
        tmpPhysicsBody->setCategoryBitmask(0x02);
        tmpPhysicsBody->setCollisionBitmask(1);
        tmpPhysicsBody->setContactTestBitmask(0x01);
        tmpPhysicsBody->setGravityEnable(false);

        Sprite* tmpSprite = Sprite::create();
        tmpSprite->setPosition(Vec2(x, y));
        tmpSprite->setAnchorPoint(Vec2::ZERO);
        tmpSprite->setContentSize(Size(width, height));
        tmpSprite->addComponent(tmpPhysicsBody);
        tmpSprite->setTag(kBarrierTag);
        tmpSprite->setName(Name::kBarrier);

        _obstacle.pushBack(tmpSprite);
        //log("x=%f,y=%f", x, y);
        this->addChild(tmpSprite, kBarrierPriority);
        //log("create barrer:%f", width);
    }
}

bool GameScene::isBarrierExist(Point position)
{
    for (auto barrier : _obstacle)
    {
        auto barrierPos = barrier->getPosition() + barrier->getContentSize() / 2;
        auto barrierSize = barrier->getContentSize();
        //log("barrierPos.x=%f,position.x=%f", barrierPos.x, position.x);
        if ((fabs(barrierPos.x - position.x) < barrierSize.width / 2) && (fabs(barrierPos.y - position.y) < barrierSize.height / 2))
        {
            //log("barrierPos.x=%f,position.x=%f", barrierPos.x, position.x);
            log("yes");
            return true;
        }
    }
    log("false");
    return false;
}

Vector<Sprite*> GameScene::getObstacle()
{
    return _obstacle;
}