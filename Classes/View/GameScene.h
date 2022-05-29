#pragma once
//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tool/SceneManager.h"
#include "Tool/MapInfo.h"
#include "Hero/HeroSprite.h"
#include "Hero/BeiyaHero.h"
#include "Tool/Timer.h"
#include "Participant/PlayerParticipant.hpp"
#include "Participant/ParticipantNode.hpp"


class GameScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(GameScene);

    virtual bool init();

    /**
    * @brief 传入主角坐标，跟踪视角
    */
    void setViewPointByPlayer(cocos2d::Point position);


    /**
    * @brief 返回值
    */
    Participant* getHero() { return _player; } 
    cocos2d::Vector<cocos2d::Sprite*> getObstacle();
    cocos2d::Vector<cocos2d::Sprite*> getGrass();

    /**
    * @brief 判断传入坐标是否有障碍层或草丛层
    * @param 要检测的坐标
    */
    bool isBarrierExist(cocos2d::Point position);
    bool isGrassExist(cocos2d::Point position);


    /**
    * @brief 使角色进入草丛变透明
    * @放在update函数中
    */
    void grassPlayerOpacity();


    /**
    * @brief 初始化地图
    * @param chooseNum=1 沙漠图
             chooseNum=2 丛林图    
             chooseNum=3 第三张图
    */
    void addMap(int chooseNum);
    //初始化对象层的10个位置
    void initObjPosition();
    //随机0-9序列容器
    std::vector<int> randTenNumberVec(int Num);

    /**
    * @初始化角色（主角）
    */
    void addHeroPlayer(); 


    /**
    * @brief 创建障碍层
    */
    void addBarrier();


    /**
    * @创建草丛
    */
    void addGrass();


    void addBox();

     /**
    * @brief 传入角色位置 返回屏幕中心的位置
    * @param 角色的位置
    */
    cocos2d::Vec2 destPos(cocos2d::Point position);


    /**
    * @brief 返回随机位置不包括障碍物
    */
    cocos2d::Vec2 randomPosWithoutBarrier();


    //暂时用不着
    cocos2d::Vec2 tiledCoordFromPosition(cocos2d::Vec2 position);


    /********* @author:王琳************/
    //schedule update
    void update(float dt);

    void addPoisonCircle();

    void initializePoiosnPhysics(cocos2d::Sprite* poison);

   


private:

    //地图信息（initMap()函数初始化了里面的变量）
    MapInfo _mapinfo;
    //障碍容器
    cocos2d::Vector<cocos2d::Sprite*> _obstacle;
    //草丛容器
    cocos2d::Vector<cocos2d::Sprite*> _grass;
    //主角
    Participant* _player;
    //所有角色的容器
    std::vector<Participant*> _heroVec; 
    //10个位置
    std::map<int, cocos2d::Vec2> _tenPosition;

    cocos2d::Sprite* poisonCircleDown;
    cocos2d::Sprite* poisonCircleUp;
    cocos2d::Sprite* poisonCircleLeft;
    cocos2d::Sprite* poisonCircleRight;
    cocos2d::Sprite* poisonDown;
    cocos2d::Sprite* poisonUp;
    cocos2d::Sprite* poisonLeft;
    cocos2d::Sprite* poisonRight;

    float poisonCircleMarch = 0.05f;
    float poisonCircleMax = 2400;
   

};



