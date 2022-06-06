/** @author  ±ÃÏ“› */

#pragma once

#include "Bullet/BulletSprite.h"

class FreezingBullet :public Bullet
{
public:
	static FreezingBullet* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override;

private:
	FreezingBullet();
};