/** @author  ±ÃÏ“› */

#pragma once

#include "Bullet/BulletSprite.h"

class PiercingBullet :public Bullet
{
public:
	static PiercingBullet* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override {}

private:
	PiercingBullet();
};