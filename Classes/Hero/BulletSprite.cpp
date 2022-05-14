//2150266 Ê±ÌìÒÝ
#include "Hero/BulletSprite.h"

USING_NS_CC;

Bullet* Bullet::createBullet(const std::string& filename)
{
    Bullet* bullet = new(std::nothrow) Bullet();
    if (bullet && bullet->initWithFile(filename))
    {
        bullet->autorelease();

        bullet->initializeBulletPhysics();

        return bullet;
    }
    else
    {
        delete bullet;
        bullet = nullptr;
        return nullptr;
    }
}

bool Bullet::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;

    return true;
}

void Bullet::initializeBulletPhysics()
{
    auto bulletPhysicsBody = PhysicsBody::createBox(this->getContentSize());
    bulletPhysicsBody->setDynamic(false);
    bulletPhysicsBody->setCategoryBitmask(0x01);
    bulletPhysicsBody->setContactTestBitmask(0x01);
    this->setPhysicsBody(bulletPhysicsBody);
    this->setName("bullet");
}