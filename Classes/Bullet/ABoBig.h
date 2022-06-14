//’≈æ∏ø≠ 2151396
#pragma once

#include "Bullet/BulletSprite.h"

class ABoBig :public Bullet
{
public:
	static ABoBig* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override {}

private:
	ABoBig();
};