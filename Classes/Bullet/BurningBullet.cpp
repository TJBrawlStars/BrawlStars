/** @author Ê±ÌìÒÝ */

#include "Bullet/BurningBullet.h"
#include "Factory/BulletFactory.h"

USING_NS_CC;

namespace {
	BulletRegister registerCreator("BurningBullet", BulletCreator(BurningBullet::create));
}

void BurningBullet::bulletEffect(Hero* hero)
{
	if (hero->isScheduled("burning")) {
		hero->unschedule("burning");
		hero->unschedule("stop burning");
	}
	hero->schedule([=](float fdelta) {hero->deductHP(hero->getHitPoint() / 10); }, 0.3, "burning");
	hero->scheduleOnce([=](float fdelta) {hero->unschedule("burning"); }, 1.5, "stop burning");
}

BurningBullet* BurningBullet::create()
{
	return new(std::nothrow)BurningBullet();
}

BurningBullet::BurningBullet()
{
	this->setBulletTecture("BulletResource/BurningBullet.png");
}