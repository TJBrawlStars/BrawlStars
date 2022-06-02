//2150266  ±ÃÏ“›

#pragma once

#include "cocos2d.h"
#include "Hero/HeroSprite.h"
#include "Participant/ParticipantNode.h"

/**
* @class Robot
* @brief derived from Participant and use template parameter to create hero
* @details the robot will automatically move and attack
*/
class Robot :public Participant
{
public:
    /** creators */
    static Robot* create();
    static Robot* createWithHeroID(std::string HeroID);

    void setAutoMove(bool state)   noexcept = delete;
    void setAutoAttack(bool state) noexcept = delete;

private:
    Robot();

    /** random engine */
    static std::default_random_engine _robotRand;
    static bool _initRand;

    /** schedule selectors */
    void autoMove(float fdelta = 1);
    void autoAttack(float fdelta = 1);
};