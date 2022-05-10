//2150266 Ê±ÌìÒÝ
#include "Hero/BulletSprite.h"

USING_NS_CC;

Bullet* Bullet::bulletCreate(const std::string& filename)
{
    Bullet* pRet = new(std::nothrow) Bullet();
    if (pRet && pRet->initWithFile(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Bullet::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
        return false;

    return true;
}