/** @author Ê±ÌìÒÝ */

#include "Participant/ParticipantNode.h"
#include "Factory/HeroFactory.h"

void Participant::setHeroType(std::string HeroID)
{
    if (!_hero) {
        _hero = HeroFactory::getInstance()->createWithClassID(HeroID);
        this->addChild(_hero);
    }
    else {
        this->removeChild(_hero);
        _hero = HeroFactory::getInstance()->createWithClassID(HeroID);
        this->addChild(_hero);
    }
}