
/** @author  ±ÃÏ“› */

#pragma once

#include "Factory/BulletFactory.h"

std::unique_ptr<BulletFactory> BulletFactory::_bulletFactoryInstance = nullptr;

std::unique_ptr<BulletFactory>& BulletFactory::getInstance()
{
	if (!_bulletFactoryInstance) {
		_bulletFactoryInstance = std::make_unique<BulletFactory>();
	}

	return _bulletFactoryInstance;
}

Bullet* BulletFactory::createWithClassID(std::string classID)
{
	auto creator = _bulletFactoryMap.find(classID);
	if (!creator->second())
		return nullptr;
	auto bullet = creator->second();

	if (bullet && bullet->initWithFile(bullet->_bulletPicture))
	{
		bullet->autorelease();

		bullet->initializeBulletPhysics();

		bullet->initializeContactListener();

		return bullet;
	}
	else
	{
		delete bullet;
		bullet = nullptr;
		return nullptr;
	}

	return bullet;
}

void BulletFactory::registerClassCreator(std::string classID, BulletCreator creator)
{
	_bulletFactoryMap.emplace(classID, creator);
}