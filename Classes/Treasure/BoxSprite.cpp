//2150266 Ê±ÌìÒÝ
#include "Treasure/TreasureBoxSprite.h"

USING_NS_CC;
using Box = TreasureBox::Box;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}
}

Box* Box::createBox()
{
    Box* box = new(std::nothrow) Box();
    if (box && box->initWithFile("box.png"))
    {
        box->autorelease();

        box->initializeBoxPhysics();

		box->initializeBloodStrip(box->_maxHealthPoint);

        return box;
    }
    else
    {
        delete box;
        box = nullptr;
        return nullptr;
    }
}

bool Box::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
		return false;

	return true;
}

void Box::initializeBoxPhysics()
{
	auto boxPhysicsBody = PhysicsBody::createBox(this->getContentSize());
	boxPhysicsBody->setDynamic(false);
	boxPhysicsBody->setCategoryBitmask(0x02);
	boxPhysicsBody->setContactTestBitmask(0x02);
	this->setPhysicsBody(boxPhysicsBody);
	this->setName("box");
}

void Box::initializeBloodStrip(const int maxHealthPoint)
{
	_bloodStrip = ui::LoadingBar::create("bloodStrip.png");
	_bloodStrip->setDirection(ui::LoadingBar::Direction::LEFT);
	_bloodStrip->setPercent(100);
	_bloodStrip->setScale(0.1);
	Size boxSize = this->getContentSize();
	_bloodStrip->setPosition(Point(boxSize.width / 2, boxSize.height + 6));
	this->addChild(_bloodStrip);
}

int Box::deductHP(const int deductPoint)
{
	if (deductPoint < 0)
		throw std::out_of_range("negative HP deduction point");

	_healthPoint = (_healthPoint - deductPoint) > 0 ? (_healthPoint - deductPoint) : 0;
	_bloodStrip->setPercent(static_cast<double>(_healthPoint) / _maxHealthPoint * 100);

	if (!_healthPoint) {
		this->setVisible(false);
		this->getPhysicsBody()->setCategoryBitmask(0x00);
		dynamic_cast<TreasureBox*>(this->getParent())->getDiamond()->getPhysicsBody()->setCategoryBitmask(0x08);
		dynamic_cast<TreasureBox*>(this->getParent())->getDiamond()->setVisible(true);
	}

	return _healthPoint;
}