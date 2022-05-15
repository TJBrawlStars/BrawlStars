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

    /********* @author:王琳************/
    //schedule update
    void update(float dt);
    

private:
    //屏幕大小
    const Vec2 kVisibleSize = Director::getInstance()->getVisibleSize();


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

///********* @author:王琳************/
//class poisonCircle :public Scene
//{
//public:
//
//    //static Scene* scene();
//    CREATE_FUNC(poisonCircle);
//
//
//
//    virtual bool init();
//
//    void updatepoisonCircle(float dt);
//
//    cocos2d::Sprite* poisonCircleDown;
//    cocos2d::Sprite* poisonCircleUp;
//    cocos2d::Sprite* poisonCircleLeft;
//    cocos2d::Sprite* poisonCircleRight;
//    float poisonCircleMarch = 0.7f;
//    float poisonCircleMax = 2400;
//
//    // int poisonCircleDamage = 10;
//    // float poisonCircleInterval = 3;
//
//    // bool poisonCircleCanDamage = true;
//
//};
