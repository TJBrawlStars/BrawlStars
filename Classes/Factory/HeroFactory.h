/** @author  ±ÃÏ“› */

#pragma once

#include "Factory/Factory.h"
#include "Hero/HeroSprite.h"
#include <memory>

typedef Hero* (*HeroCreator)(void);
typedef std::unordered_map<std::string, HeroCreator> HeroFactoryMap;

class HeroFactory :protected Factory
{
public:
	static std::shared_ptr<HeroFactory> getInstance();
	Hero* createWithClassID(std::string classID);

	void registerClassCreator(std::string classID, HeroCreator creator);

protected:

private:
	static std::shared_ptr<HeroFactory> _heroFactoryInstance;
	HeroFactoryMap _heroFactoryMap;
};

class HeroRegister
{
public:
	HeroRegister(std::string classID, HeroCreator creator)
	{
		HeroFactory::getInstance()->registerClassCreator(classID, creator);
	}
	HeroRegister() = delete;
};