/** @author  ±ÃÏ“› */

#pragma once

#include "Factory/HeroFactory.h"

std::shared_ptr<HeroFactory> HeroFactory::_heroFactoryInstance = nullptr;

std::shared_ptr<HeroFactory> HeroFactory::getInstance()
{
	if (!_heroFactoryInstance) {
		_heroFactoryInstance = std::make_shared<HeroFactory>();
	}

	return _heroFactoryInstance;
}

Hero* HeroFactory::createWithClassID(std::string classID)
{
	auto creator = _heroFactoryMap.find(classID);

	if (creator->second)
		return creator->second();
	else
		return nullptr;
}

void HeroFactory::registerClassCreator(std::string classID, HeroCreator creator)
{
	_heroFactoryMap.emplace(classID, creator);
}