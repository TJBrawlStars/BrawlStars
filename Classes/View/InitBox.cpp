//2152590 ЭѕСе

#include"GameScene.h"
#include"Treasure/TreasureBoxSprite.h"


void GameScene::addBox()
{

	for (int i = 0; i < 10; ++i)
	{
		auto _box = TreasureBox::createTreasureBox();
		_box->setPosition(randomPosWithoutBarrier());
		this->addChild(_box);
	}
}