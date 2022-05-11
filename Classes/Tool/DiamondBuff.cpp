#include "DiamondBuff.h"
USING_NS_CC;

bool DiamondBuff::init()
{
	if(!Item::init())
	    return false;

	_sprite = Sprite::create(Path::Diamond);

	if (_sprite == nullptr)
	{
		log("create diamond failed,not find the image");
	}
	else
	{
		log("create diamond successfully");
		this->addChild(_sprite);
		//log("This box's corrdinate is %d %d", posX, posY);
		generatePhysicalBody(Name::kDiamond, kDiamondTag);
	}

	return true;
}

int DiamondBuff::buffAttackOrHealth()
{
	int rand = random(0, 1);
	if (rand == static_cast<int>(Buff::attack))
	{
		log("attack buff create");
		return kBuffAttack;
	}
	else if (rand == static_cast<int>(Buff::health))
	{
		log("health buff create");
		return kBuffHealth;
	}
}
