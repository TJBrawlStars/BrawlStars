/** @author  ±ÃÏ“› */

#pragma once

#include "Bullet/BulletSprite.h"

class BurningBullet :public Bullet
{
public:
	static BurningBullet* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override;

private:
	BurningBullet();
};