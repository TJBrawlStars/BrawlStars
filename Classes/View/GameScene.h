#pragma once

//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
USING_NS_CC;
#include"ui/CocosGUI.h"
using namespace ui;
#include"Tool/SceneManager.h"

class GameScene : public Scene
{
public:

    CREATE_FUNC(GameScene);

private:

    virtual bool init();

private:

    const Vec2 kVisibleSize = Director::getInstance()->getVisibleSize();

};