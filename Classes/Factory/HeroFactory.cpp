/** @author  ±ÃÏ“› */

#pragma once

#include "Factory/HeroFactory.h"

std::unique_ptr<HeroFactory> HeroFactory::_heroFactoryInstance = nullptr;

std::unique_ptr<HeroFactory>& HeroFactory::getInstance()
{
	if (!_heroFactoryInstance) {
		_heroFactoryInstance = std::make_unique<HeroFactory>();
	}

	return _heroFactoryInstance;
}

Hero* HeroFactory::createWithClassID(std::string classID)
{
	auto creator = _heroFactoryMap.find(classID);
	if (!creator->second())
		return nullptr;
	auto hero = creator->second();

	if (hero)
	{
		hero->autorelease();

		//initialilze the sprite
		hero->initializeHeroSprite();

		//initialize the physics body
		hero->initializeHeroPhysics();

		//draw the blood strip
		hero->initializeBloodStrip();

		//draw the ammo strip
		hero->initializeAmmoStrip(hero->_maxAmmo);

		//draw the energy strip
		hero->initializeEnergyStrip();

		//dispaly the number of diamonds
		hero->initializeDiamondDisplay();

		return hero;
	}
	else
	{
		delete hero;
		hero = nullptr;
		return nullptr;
	}

	return hero;
}

void HeroFactory::registerClassCreator(std::string classID, HeroCreator creator)
{
	_heroFactoryMap.emplace(classID, creator);
}