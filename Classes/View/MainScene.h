#pragma once

//#define NDEBUG
#include<cassert>
#include "cocos2d.h"
USING_NS_CC;
#include"ui/CocosGUI.h"
using namespace ui;
#include "LoadingScene.h"
#include "RoomLayer.h"

class LoadingScene;
class RoomLayer;

/**
   * @brief 主场景
   */
class MainScene : public Scene
{
public:

    CREATE_FUNC(MainScene);

private:

    virtual bool init();

    /**
    * @brief 设置按钮并add进场景
    * @param (Vec2 position)位置
    * @param (std::string pic_name)图片路径
    */
    Button* ButtonCreate(Vec2 position, std::string pic_name1, std::string pic_name2 = "");

private:

    const Vec2 kVisibleSize = Director::getInstance()->getVisibleSize();

    //主界面背景
    Sprite* _bg = NULL;

    //loading层
   LoadingScene* _loading = NULL;

   //菜单
   Button* _menu_button = NULL;

   //个人信息
   Button* _info_button = NULL;

   Button* _play_button = NULL;

   Sprite* _figure = NULL;

   //房间层
   RoomLayer* _room = NULL;
};

