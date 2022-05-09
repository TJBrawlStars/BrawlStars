#include "TreasureBox.h"
USING_NS_CC;

TreasureBox* TreasureBox::createBox()
{
	return TreasureBox::create();
}

bool TreasureBox::init()
{
	if (!Node::init())
		return false;
	//°ó¶¨±¦Ïä¾«ÁéÍ¼Æ¬
	_sprite = Sprite::create(Path::BoxClose);

	if (_sprite == nullptr)
	{
		log("create box failed,not find the image");
	}
	else
	{
		log("create successfully");
		this->addChild(_sprite);//m_pSprite bind with the box object   ???
		const int posX = random(32, maxWidth - 32);
		const int posY = random(32, maxHeight - 32);
		this->setPosition(posX, posY);
		log("This box's corrdinate is %d %d", posX, posY);
		generatePhysicalBody("TreasureBox", kBoxTag);
	}

	return true;
}