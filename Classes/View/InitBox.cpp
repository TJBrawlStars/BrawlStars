//2152590 ����

#include"GameScene.h"
#include"Treasure/TreasureBoxSprite.h"


void GameScene::addBox()
{
	//������������ڵ�ͼ�ϣ��������ϰ����λ��
	for (int i = 0; i < 10; ++i)
	{
		auto _box = TreasureBox::createTreasureBox();
		_box->setPosition(randomPosWithoutBarrier());
		this->addChild(_box);
	}
}