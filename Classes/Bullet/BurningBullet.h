/** @author  ±ÃÏ“› */

#pragma once

#include "Bullet/BulletSprite.h"

class BurningBullet :public Bullet
{
public:
	static BurningBullet* create();

protected:
	/** overrides */
	void bulletEffect(Hero* hero) override;

private:
	BurningBullet();
};