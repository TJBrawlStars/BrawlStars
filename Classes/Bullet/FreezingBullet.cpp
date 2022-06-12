/** @author Ê±ÌìÒÝ */

#include "Bullet/FreezingBullet.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	BulletRegister registerCreator("FreezingBullet", BulletCreator(FreezingBullet::create));
}

void FreezingBullet::effectOnHero(Hero* hero)
{
	hero->setMoveSpeed(Hero::Level::LOW);
	if (hero->isScheduled(SEL_SCHEDULE(&Hero::resetMoveSpeed)))
		hero->unschedule(SEL_SCHEDULE(&Hero::resetMoveSpeed));
	hero->scheduleOnce(SEL_SCHEDULE(&Hero::resetMoveSpeed), 1.5);
}

FreezingBullet* FreezingBullet::create()
{
	return new(std::nothrow)FreezingBullet();
}

FreezingBullet::FreezingBullet()
{
	this->setBulletTecture("BulletResource/FreezingBullet.png");
}