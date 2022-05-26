#include "Tool/Timer.h"

inline void MyTimer::restart()
{
    _start_time = std::chrono::steady_clock::now();
}

inline double MyTimer::elapsed(bool restart)
{
    _end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = _end_time - _start_time;
    if (restart)
        this->restart();
    return diff.count() * 1000;
}

void MyTimer::rlog(const std::string& tip)
{
    log(true, tip, true, false);
}

void MyTimer::log(bool reset, const std::string& tip, bool unit_ms, bool kill)
{
    if (unit_ms) {
        if (tip.length() > 0)
            std::cout << tip + ":" << static_cast<int>(elapsed()) << "ms" << std::endl;
        else
            std::cout << _name << static_cast<int>(elapsed()) << "ms" << std::endl;
    }
    else {
        if (tip.length() > 0)
            std::cout << tip + ":" << static_cast<int>(elapsed() / 1000.0) << "s" << std::endl;
        else
        {
            std::cout << _name << std::to_string(static_cast<int>(elapsed() / 1000.0) / 3600) 
                        << ":" << std::to_string(static_cast<int>(elapsed() / 1000.0) / 60) 
                        << ":" << std::to_string(static_cast<int>(elapsed() / 1000.0) / 3600) 
                << std::endl;
        }
    }

    int i = (int)('c');

    if (reset)
        this->restart();

    if (kill)
        exit(5);
}

void MyTimer::createUI()
{
    _timerInfoBG = cocos2d::Sprite::create("UI/SEUITime.png");
    _timerInfoBG->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    _timerInfoBG->setScaleY(0.24f);
    _timerInfoBG->setScaleX(0.3f);

    _timerInfo = cocos2d::Label::createWithTTF("", "fonts/arial.ttf", 22);
    _timerInfo->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

    this->addChild(_timerInfoBG);
   _timerInfoBG->setGlobalZOrder(kFightUI);
    this->addChild(_timerInfo);
    _timerInfo->setGlobalZOrder(kFightUI);

    this->schedule(CC_SCHEDULE_SELECTOR(MyTimer::update));
}

void MyTimer::update(float dlt)
{
    auto parentNode = dynamic_cast<GameScene*>(this->getParent());
    auto visibleSize = Director::getInstance()->getVisibleSize();

    _timerInfoBG->setPosition(parentNode->destPos(parentNode->getHero()->getPosition()) + Vec2(-visibleSize.width / 2, visibleSize.height / 2));
    _timerInfo->setPosition(parentNode->destPos(parentNode->getHero()->getPosition()) + Vec2(55-visibleSize.width / 2, visibleSize.height / 2));
    _timerInfo->setString((getHour()+":"+getMinute()+":"+getSecond()));
}
