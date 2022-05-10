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
        , _continue(NULL), _bg(NULL) {};

    /**
    * @brief 从游戏控制器中读出胜利方，然后在指定一边显示win
    */
    void WhoWin();

    /**
    * @brief 从游戏控制器中读出我方和敌方的hero然后把照片贴上来,然后对应的战绩也要有,在底下+标签叭
    */
    void ShowRecord();

private:
     
    const cocos2d::Size kVisibleSize;
    
    //继续按钮
    cocos2d::ui::Button* _continue;

    //背景
    cocos2d::Sprite* _bg;

};