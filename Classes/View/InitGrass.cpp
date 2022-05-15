/**
* @author ÕÅ¾¸¿­
* @brief ³õÊ¼»¯²Ý´Ô
*/
#include"cocos2d.h"
#include "View\GameScene.h"
#include "Const/Const.h"
using namespace std;
USING_NS_CC;

void GameScene::addGrass()
{
    auto group = _mapinfo._map->getObjectGroup("grass");
    ValueVector grassObjects = group->getObjects();

    for (auto grass : grassObjects)
    {
        ValueMap& dict = grass.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        PhysicsBody* tmpPhysicsBody = PhysicsBody::createBox(Size(width, height),
            PhysicsMaterial(100.0f, 0.0f, 0.0f));
        tmpPhysicsBody->setDynamic(false);
        //²Ý´ÔµÄ
        tmpPhysicsBody->setCategoryBitmask(0x02);
        tmpPhysicsBody->setCollisionBitmask(1);
        tmpPhysicsBody->setContactTestBitmask(0x01);
        tmpPhysicsBody->setGravityEnable(false);

        Sprite* tmpSprite = Sprite::create();
        tmpSprite->setPosition(Vec2(x, y));
        tmpSprite->setAnchorPoint(Vec2::ZERO);
        tmpSprite->setContentSize(Size(width, height));
        tmpSprite->addComponent(tmpPhysicsBody);
        tmpSprite->setTag(kGrassTag);
        tmpSprite->setName(Name::kGrass);

        _grass.pushBack(tmpSprite);
        //log("x=%f,y=%f", x, y);
        this->addChild(tmpSprite, kGrassPriority);
        log(" grass:%f", width);
    }
}

void GameScene::inTimerViewScreen()
{
    
}

bool GameScene::isGrassExist(cocos2d::Point position)
{
    for (auto grass : _grass)
    {
        auto grassPos = grass->getPosition() + grass->getContentSize() / 2;
        auto grassSize = grass->getContentSize();
        //log("barrierPos.x=%f,position.x=%f", barrierPos.x, position.x);
        if ((fabs(grassPos.x - position.x) < grassSize.width / 2) && (fabs(grassPos.y - position.y) < grassSize.height / 2))
        {
            //log("barrierPos.x=%f,position.x=%f", barrierPos.x, position.x);
            log("yes");
            return true;
        }
    }
    log("false");
    return false;
}

Vector<Sprite*> GameScene::getGrass()
{
    return _grass;
}

void GameScene::grassPlayerOpacity()
{
    if (isGrassExist(_player->getPosition()))
        _player->setOpacity(100);
    else
        _player->setOpacity(255);
}