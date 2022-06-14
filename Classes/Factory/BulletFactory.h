/** @author  ±ÃÏ“› */

#pragma once

#include "Factory/Factory.h"
#include "Bullet/BulletSprite.h"
#include <memory>

typedef Bullet* (*BulletCreator)(void);
typedef std::unordered_map<std::string, BulletCreator> BulletFactoryMap;

class BulletFactory :protected Factory
{
public:
	static std::unique_ptr<BulletFactory>& getInstance();
	Bullet* createWithClassID(std::string classID);

	void registerClassCreator(std::string classID, BulletCreator creator);

protected:

private:
	static std::unique_ptr<BulletFactory> _bulletFactoryInstance;
	BulletFactoryMap _bulletFactoryMap;
};

class BulletRegister
{
public:
	BulletRegister(std::string classID, BulletCreator creator)
	{
		BulletFactory::getInstance()->registerClassCreator(classID, creator);
	}
	BulletRegister() = delete;
};