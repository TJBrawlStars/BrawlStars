//2150266 Ê±ÌìÒÝ

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"

/**
* @class Participant
* @brief the participants of game which has the informaiton of hero and username
*/
class Participant :public cocos2d::Node
{
public:
	/** overrides */
	virtual void setPosition(const cocos2d::Vec2& position) override { return _hero->setPosition(position); }
	virtual void setPosition(float x, float y)              override { return _hero->setPosition(x, y); }
	virtual const cocos2d::Vec2& getPosition() const        override { return _hero->getPosition(); }

	bool alive()              const noexcept { return _hero->alive(); }
	std::string getUserName() const noexcept { return _userName; }

protected:
	std::string _userName = "???";  ///< the participant's name
	std::string _heroid;            ///< use hero id to create hero
	Hero* _hero;                    ///< the hero the participant use

	/** instantiation is not allowed */
	Participant() = default;
	void setParticipant() = delete;

private:

};