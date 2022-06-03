/** @author  ±ÃÏ“› */

#pragma once

#include "Bullet/BulletSprite.h"

class NormalBullet :public Bullet
{
public:
	static NormalBullet* create();

protected:
	/** overrides */
	void bulletEffect(Hero* hero) override {}

private:
	NormalBullet();
};