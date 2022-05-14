#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 主界面的好友层
*/
class FriendLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(FriendLayer);

private:

    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) { return true; }

    FriendLayer() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        , _bg(NULL), _back(NULL), _text(NULL) {};

private:

    const cocos2d::Size kVisibleSize;

    //背景
    cocos2d::Sprite* _bg;

    //返回按钮
    cocos2d::ui::Button* _back;

    //添加好友按钮
    cocos2d::ui::Button* _addFriend;

    //文本框
    cocos2d::ui::TextField* _text;

};

