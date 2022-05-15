#pragma once
//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"Tool/SceneManager.h"
#include "Tool/MapInfo.h"
#include"Hero/HeroSprite.h"
#include"Hero/BeiyaHero.h"
#include"Tool/Timer.h"

class GameScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(GameScene);

    virtual bool init();

    /********* @author:张靖凯************/

    //传入主角的坐标，放在控制器（控制角色）当中
    void setViewPointByPlayer(cocos2d::Point position);

    Beiya* getBeiya() { return _player; };

    //判断是否碰撞障碍物（有bug！）(暂时不用)
    //传入的是openGL坐标(就是左下角为原点，2400*2400）向右为x向上为y
    //bool isColliding(Vec2 position);


    //转换成瓦片坐标（左上角为原点）
    cocos2d::Vec2 tiledCoordFromPosition(cocos2d::Vec2 position);


    //返回障碍层/草丛
    cocos2d::Vector<cocos2d::Sprite*> getObstacle();
    cocos2d::Vector<cocos2d::Sprite*> getGrass();


    //判断是否有障碍物/草丛,有则返回true
    bool isBarrierExist(cocos2d::Point position);
    bool isGrassExist(cocos2d::Point position);

    void grassPlayerOpacity();

    //初始化地图
    void addMap();


    //初始化角色
    void addHeroPlayer();
    

    //void addAIHeroPlayer(); 
    

    //创建障碍层
    void addBarrier();


    //创建草丛
    void addGrass();

    void inTimerViewScreen();

    //屏幕中心的位置
    Vec2 destPos(Point position);

    ////时间的UI
    //void setTimeUI(MyTimer& timer);
    /********* @author:王琳************/
    
    void update(float dt);

private:
    //屏幕大小
    const cocos2d::Vec2 kVisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    /********* @author:张靖凯************/

    //地图信息（initMap()函数初始化了里面的变量）
    MapInfo _mapinfo;
    //障碍容器
    cocos2d::Vector<cocos2d::Sprite*> _obstacle;
    //草丛容器
    cocos2d::Vector<cocos2d::Sprite*> _grass;
    //主角
    Beiya* _player;
   
};


