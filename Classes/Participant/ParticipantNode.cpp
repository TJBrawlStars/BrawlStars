/** @author Ê±ÌìÒÝ */

#include "Participant/ParticipantNode.h"
#include "Factory/HeroFactory.h"

void Participant::setHeroType(std::string heroID)
{
    if (!_hero) {
        _hero = HeroFactory::getInstance()->createWithClassID(heroID);
        this->addChild(_hero);
        this->_heroID = heroID;
    }
    else {
        this->removeChild(_hero);
        _hero = HeroFactory::getInstance()->createWithClassID(heroID);
        this->addChild(_hero);
        this->_heroID = heroID;
    }
}