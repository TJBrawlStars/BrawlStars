#include "TreasureBox.h"
USING_NS_CC;

TreasureBox* TreasureBox::createBox()
{
	return TreasureBox::create();
}

//void TreasureBox::setBoxPos(cocos2d::Vec2 position)
//{
//	_boxPos = position;
//}

void TreasureBox::initialzeBloodStrip(const int maxBoxHealthPoint)
{
	_bloodStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_bloodStrip->setPercent(100);
	_bloodStrip->setScale(0.08f);
	Size boxSize = this->getContentSize();
	_bloodStrip->setPosition(Point(boxSize.width / 2, boxSize.height + 25));
	this->addChild(_bloodStrip);
}

int TreasureBox::deductHP(int deductPoint)
{
	if (deductPoint < 0)
		throw std::out_of_range("negative HP deduction point");

	_healthPoint = (_healthPoint - deductPoint) > 0 ? (_healthPoint - deductPoint) : 0;
	if (_healthPoint == 0)
		openBox();//没血了就打开宝箱

	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	return _healthPoint;
}

bool TreasureBox::init()
{
	if (!Node::init())
		return false;
	//绑定宝箱精灵图片
	_sprite = Sprite::create(Path::BoxClose);

	if (_sprite == nullptr)
	{
		log("create box failed,not find the image");
	}
	else
	{
		log("create successfully");
		this->addChild(_sprite);//添加到了Treasure上，不需要tag
		//const int posX = random(32, maxWidth - 32);
		//const int posY = random(32, maxHeight - 32);
		//_boxPos = Vec2(posX, posY);
		//this->setPosition(_boxPos);
		//log("This box's corrdinate is %d %d", _boxPos.x, _boxPos.y);
		generatePhysicalBody(Name::kTreasureBox, kBoxTag);
	}

	return true;
}

void TreasureBox::openBox()
{
	auto boxPos = this->getPosition();
	//场景节点
	auto myParent = this->getParent(); 

	//首先的宝箱消失
	this->removeFromParentAndCleanup(true);

	//宝箱换图
	auto boxOver = Sprite::create(Path::BoxOpen);
	myParent->addChild(boxOver, kBoxPriority);
	auto stayAction = DelayTime::create(0.4f);
	boxOver->runAction(stayAction);
	boxOver->removeFromParentAndCleanup(true);

	//掉出宝石
	auto diamond = DiamondBuff::create();
	myParent->addChild(diamond, kDiamondPriority);
	diamond->setPosition(boxPos);
	auto action = JumpBy::create(1.0f, boxPos, 40, 1);
	diamond->runAction(action);

	//接触宝箱事件
	
	///
}