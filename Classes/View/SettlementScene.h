#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
 * @brief 结算场景
 */
class SettlementScene : public cocos2d::Scene
{
public:

    CREATE_FUNC(SettlementScene);

private:

    virtual bool init();

    SettlementScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        , _continue(NULL), _bg(NULL), _figure(NULL), _cups(NULL), _money(NULL) {};

    /**
    * @brief 从游戏控制器中读出名次顺序，分配奖励
    */
    void Win();

    ///**
    //* @brief 从游戏控制器中读出我方和敌方的hero然后把照片贴上来,然后对应的战绩也要有,在底下+标签叭
    //*/
    //void ShowRecord();

private:
     
    const cocos2d::Size kVisibleSize;
    
    //继续按钮
    cocos2d::ui::Button* _continue;

    //背景
    cocos2d::Sprite* _bg;

    //玩家英雄展示
    cocos2d::Sprite* _figure;

    //获得奖杯数
    cocos2d::Label* _cups;

    //获得金币数
    cocos2d::Label* _money;

};