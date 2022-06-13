/** @author Ê±ÌìÒÝ */

#include "Bullet/NormalBullet.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	BulletRegister registerCreator("NormalBullet", BulletCreator(NormalBullet::create));
}

NormalBullet* NormalBullet::create()
{
	return new(std::nothrow)NormalBullet();
}

NormalBullet::NormalBullet()
{
	this->setBulletTecture("BulletResource/NormalBullet.png");
}