#include"GameScene.h"
#include"Treasure/TreasureBoxSprite.h"
#include<vector>

void GameScene::addBox()
{
	//宝箱随机出现在地图上，不包括障碍物的位置
	for (int i = 0; i < 10; ++i)
	{
		auto _box = TreasureBox::createTreasureBox();
		_box->setPosition(randomPosWithoutBarrier());
		this->addChild(_box);
	}
}