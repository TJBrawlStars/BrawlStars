//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"

/**
* @class Bullet
* @brief bullets of hero
* @details Bullet is the child of Hero's parent node
*/
class Bullet :public cocos2d::Sprite {
public:
	enum class Effect { NONE, FREEZE, BURN };

	static Bullet* createBullet(const std::string& filename);

	int hitPoint()  const noexcept { return _hitPoint; }
	Effect effect() const noexcept { return _effect; }

	void sethitPoint(int hitPoint) noexcept { _hitPoint = hitPoint; }
	void setEffect(Effect effect) noexcept { _effect = effect; }

private:
	bool initWithFile(const std::string& filename);
	CREATE_FUNC(Bullet)

	int _hitPoint = 0;              ///< the hit point of the bullet which is related to hero
	Effect _effect = Effect::NONE;  ///< the special effect of bullet
	std::string _bulletPicture;     ///< the picture of bullet
};