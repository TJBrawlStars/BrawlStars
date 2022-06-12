/** @author ʱ���� */

#pragma once

#include "Bullet/BulletSprite.h"

class NormalBullet :public Bullet
{
public:
	static NormalBullet* create();

protected:
	/** overrides */
	void effectOnHero(Hero* hero) override {}

private:
	NormalBullet();
};