#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

class HeroFactory;
class MainScene;

/**
* @brief 初始的登录场景,实际上继承自Layer然后贴在main场景上
*/
class FigureLayer : public cocos2d::Layer
{
public:

    CREATE_FUNC(FigureLayer);

private:

    /**
    * @brief 参数记录主画面，同步更改主界面上人物
    */
    virtual bool init();

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) { return true; }

    //这里不能给std::string赋空指针，草坑死我了,NULL用习惯了，应该是使用了空指针系统不晓得这个string有多长了
    FigureLayer() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        ,  _bg(NULL), _back(NULL), _figure(""), _select(NULL) 
    {
    };

    /**
    * @brief 显示现有角色
    */
    void SetFigures();

private:

    //现有英雄名字
    static std::vector<std::string> heroVec;

    const cocos2d::Size kVisibleSize;

    //现有角色个数,在初始化的地方改数值，相当于#define
    int kNum;

    //背景
    cocos2d::Sprite* _bg;

    //返回按钮
    cocos2d::ui::Button* _back;

    //现有人物
    cocos2d::Vector<cocos2d::ui::Button*> _figures;

    //当前人物
    std::string _figure;

    //记录select标志
    cocos2d::Sprite* _select;

};

