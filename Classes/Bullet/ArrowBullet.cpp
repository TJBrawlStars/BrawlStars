//张靖凯 2151396
#include "Bullet/ArrowBullet.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

//ƽA
namespace {
	BulletRegister registerCreator("ArrowBullet", BulletCreator(ArrowBullet::create));
}

ArrowBullet* ArrowBullet::create()
{
	return new(std::nothrow)ArrowBullet();
}

ArrowBullet::ArrowBullet()
{
	this->setBulletTecture("BulletResource/arrow.png");
}

