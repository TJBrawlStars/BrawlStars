//2150266 Ê±ÌìÒÝ
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
	this->addChild(_box);
	this->addChild(_diamond);
}