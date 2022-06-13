//2150266 Ê±ÌìÒİ
#include "Treasure/TreasureBoxSprite.h"

USING_NS_CC;

TreasureBox* TreasureBox::createTreasureBox()
{
	return TreasureBox::create();
}

TreasureBox::TreasureBox()
{
	_box = Box::createBox();
	_diamond = Diamond::createDiamond();
	_box->setExist(true);
	_diamond->setExist(false);
	_box->setPosition(0, 0);
	_diamond->setPosition(0, 0);
	this->addChild(_box);
	this->addChild(_diamond);
	this->setName("treasure");
}