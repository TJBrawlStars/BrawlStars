/** @author Ê±ÌìÒÝ */

#include "Bullet/PiercingBullet.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	BulletRegister registerCreator("PiercingBullet", BulletCreator(PiercingBullet::create));
}

PiercingBullet* PiercingBullet::create()
{
	return new(std::nothrow)PiercingBullet();
}

PiercingBullet::PiercingBullet()
{
	this->setBulletTecture("BulletResource/PiercingBullet.png");
}