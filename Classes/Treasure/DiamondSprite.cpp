//2150266 Ê±ÌìÒÝ
#include "Treasure/TreasureBoxSprite.h"

USING_NS_CC;
using Diamond = TreasureBox::Diamond;

std::default_random_engine Diamond::_diamondRand;
bool Diamond::_initRand = false;

Diamond* Diamond::createDiamond()
{
    Diamond* diamond = new(std::nothrow) Diamond();
    if (diamond && diamond->initWithFile("diamond.png"))
    {
        diamond->autorelease();

        diamond->initializeDiamondPhysics();

        if (!_initRand) {
            _diamondRand.seed(time(0));
            _initRand = true;
        }

        return diamond;
    }
    else
    {
        delete diamond;
        diamond = nullptr;
        return nullptr;
    }
}

Diamond* Diamond::dropDiamond(Point dropPoint)
{
    auto diamond = Diamond::createDiamond();
    std::uniform_real_distribution<double> u(-15, 15);
    float x = dropPoint.x + u(_diamondRand);
    float y = dropPoint.y + u(_diamondRand);
    diamond->setPosition(Point(x, y));

    return diamond;
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

const Vec2& Diamond::getPosition() const
{
    if (this->getParent()->getName() == "treasure")
        return this->getParent()->getPosition();
    else
        return Node::getPosition();
}

void Diamond::setExist(bool exist)
{
    if (exist) {
        this->setVisible(true);
        this->getPhysicsBody()->setCategoryBitmask(0x08);
        this->setName("diamond");
    }
    else {
        this->setVisible(false);
        this->getPhysicsBody()->setCategoryBitmask(0x00);
        this->setName("null");
    }
}