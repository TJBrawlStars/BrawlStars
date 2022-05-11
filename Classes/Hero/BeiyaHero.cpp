//2150266 Ê±ÌìÒÝ
#include "Hero/BeiyaHero.h"

USING_NS_CC;

namespace {
	// Print useful error message instead of segfaulting when files are not there.
	void problemLoading(std::string filename)
	{
		printf("Error while loading: %s\n", filename);
		printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	}
}

Beiya* Beiya::createBeiya()
{
	auto beiya = Beiya::create();

	//initialize the physics body
	beiya->initializeHeroPhysics(beiya);

	//draw the blood strip
	beiya->initialzeBloodStrip(beiya->_maxHealthPoint);

	return beiya;
}

const std::string Beiya::_beiyaPicture = "player.png";

Beiya::Beiya() :Hero(3360, 1)
{
	_healthPoint = _maxHealthPoint;
	_ammo = _maxAmmo;
	_hitPoint = 1120;
	_moveSpeed = Level::MEDIUM;
	_shotRange = Level::HIGH;
	_loadSpeed = Level::EXTREME_HIGH;
}

bool Beiya::init()
{
	if (!Sprite::init())
		return false;

    _fileName = _beiyaPicture;

    Texture2D* texture = _director->getTextureCache()->addImage(_beiyaPicture);
    if (texture)
    {
        Rect rect = Rect::ZERO;
        rect.size = texture->getContentSize();
        return initWithTexture(texture, rect);
    }

    // don't release here.
    // when load texture failed, it's better to get a "transparent" sprite then a crashed program
    // this->release();
    return false;
}

bool Beiya::attack(Touch* touch, Event* event)
{
	/** @note the animation of attack */
	//get the location of touch point
	Point touchLocation = touch->getLocation();
	//convert the location to offset
	Vec2 offset = touchLocation - this->getPosition();

	//add projectile
	auto projectile = Bullet::bulletCreate("projectile.png");
	if (projectile == nullptr)
		problemLoading("projectile.png");
	projectile->sethitPoint(this->getHitPoint());
	projectile->setPosition(this->getPosition());
	initializeBulletPhysics(projectile);
	this->getParent()->addChild(projectile);

	//get the vector of attack according to the range of hero
	offset.normalize();
	Vec2 attackVec = offset * 50 * static_cast<int>(_shotRange);

	//create the animation
	auto shot = MoveBy::create(static_cast<float>(_shotRange) / 5, attackVec);
	auto removeBullet = RemoveSelf::create();
	projectile->runAction(Sequence::create(shot, removeBullet, nullptr));

	/** @note modify hero attributes */
	--_ammo;
	if (_ammo == _maxAmmo - 1)
		startLoading();

	return true;
}