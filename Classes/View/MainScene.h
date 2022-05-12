#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

class LoadingScene;
class RoomLayer;
class SettingLayer;
class FigureLayer;
class InforLayer;

   /**
   * @brief 主场景
   */
class MainScene : public cocos2d::Scene
{
public:

    CREATE_FUNC(MainScene);

    /**
    * @brief 设置主界面展示角色
    */
    void SetFigure(const std::string& filename);

    /**
    * @brief 读取展示角色的文件
    */
    std::string GetFigure()const;

    /**
    * @brief 取得当前主场景
    */
    static  MainScene* GetMainScene() { return _that; }

private:

    virtual bool init();

    MainScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        , _bg(NULL), _loading(NULL), _menu_button(NULL), _info_button(NULL), _play_button(NULL)
        , _figure(NULL), _room(NULL), _set(NULL), _back(NULL), _changeFigure(NULL), _info(NULL) {};

private:

    const cocos2d::Size kVisibleSize;

    //记录当前主场景，给贴在主界面上的层用
    static MainScene* _that;

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
   cocos2d::ui::Button* _figure;

   //房间层
   RoomLayer* _room;

   //设置层
   SettingLayer* _set;

   //返回按钮
   cocos2d::ui::Button* _back;

   //选择角色层
   FigureLayer* _changeFigure;

   //info层
   InforLayer* _info;

};

