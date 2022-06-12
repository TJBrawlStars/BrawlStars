//’≈æ∏ø≠ 2151396
#pragma once

#include "Bullet/BulletSprite.h"

class ArrowBullet :public Bullet
{
public:
	static ArrowBullet* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override {}

private:
	ArrowBullet();
};

