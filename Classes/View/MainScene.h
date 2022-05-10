#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

class LoadingScene;
class RoomLayer;
class SettingLayer;

   /**
   * @brief 主场景
   */
class MainScene : public cocos2d::Scene
{
public:

    CREATE_FUNC(MainScene);

private:

    virtual bool init();

    //弃用

    //**
    //* @brief 设置按钮并add进场景,有两个重载版本
    //* @param (Vec2 position)位置
    //* @param (std::string pic_name)图片路径
    //* @param (std::string words)文字按钮的显示文字
    //*/
    //cocos2d::ui::Button* ButtonCreate(const cocos2d::Vec2&& position, const std::string&& pic_name);
    //cocos2d::ui::Button* ButtonCreate(const std::string&& words,const cocos2d::Vec2&& position);

    MainScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        , _bg(NULL), _loading(NULL), _menu_button(NULL), _info_button(NULL), _play_button(NULL)
        , _figure(NULL), _room(NULL), _set(NULL), _back(NULL) {};

private:

    const cocos2d::Size kVisibleSize;

    //主界面背景
    cocos2d::Sprite* _bg;

    //loading层
   LoadingScene* _loading;

   //菜单
   cocos2d::ui::Button* _menu_button;

   //个人信息
   cocos2d::ui::Button* _info_button;

   //开始游戏按钮
   cocos2d::ui::Button* _play_button;

   //场景中显示人物形象
   cocos2d::Sprite* _figure;

   //房间层
   RoomLayer* _room;

   //设置层
   SettingLayer* _set;

   //返回按钮
   cocos2d::ui::Button* _back;

};

