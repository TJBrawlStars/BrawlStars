//2150266 Ê±ÌìÒÝ
#include "Treasure/TreasureBoxSprite.h"

USING_NS_CC;
using Diamond = TreasureBox::Diamond;

Diamond* Diamond::createDiamond()
{
    Diamond* diamond = new(std::nothrow) Diamond();
    if (diamond && diamond->initWithFile("diamond.png"))
    {
        diamond->autorelease();

        diamond->initializeDiamondPhysics();

        return diamond;
    }
    else
    {
        delete diamond;
        diamond = nullptr;
        return nullptr;
    }
}

bool Diamond::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;

    return true;
}

void Diamond::initializeDiamondPhysics()
{
    auto diamondPhysicsBody = PhysicsBody::createBox(this->getContentSize());
    diamondPhysicsBody->setDynamic(false);
    diamondPhysicsBody->setCategoryBitmask(0x08);
    diamondPhysicsBody->setContactTestBitmask(0x08);
    this->setPhysicsBody(diamondPhysicsBody);
    this->setName("diamond");
}