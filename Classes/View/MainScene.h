#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include "Tool/ChatBox.h"

class LoadingScene;
class RoomLayer;
class SettingLayer;
class FigureLayer;
class InforLayer;
class MenuLayer;
class FriendLayer;

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

    /**
    * @brief 重置
    */
    static void Reset() { _that = NULL; }

    /**
    * @brief 修改头像
    */
    void SetInfo(const std::string& filename);

    /**
    * @brief 得到头像
    */
    std::string GetInfo();

    /**
    * @brief 用于登陆后初始化主场景上的图像
    */
    void Load();

private:

    virtual bool init();

    MainScene() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
        , _bg(NULL), _loading(NULL), _menu_button(NULL), _info_button(NULL), _play_button(NULL)
        , _figure(NULL), _room(NULL), _menu(NULL), _back(NULL), _changeFigure(NULL), _info(NULL)
        , _friends(NULL) {};

    void updateChatBoxPosition();

    //schedule update
    void update(float dt);

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

   //菜单层
   MenuLayer* _menu;

   //返回按钮
   cocos2d::ui::Button* _back;

   //选择角色层
   FigureLayer* _changeFigure;

   //info层
   InforLayer* _info;

   //好友按钮
   cocos2d::ui::Button* _friends;

   //friend层
   FriendLayer* _friend;

   //消息按钮 
   cocos2d::ui::Button* _messages;

   //聊天框按键
   virtual bool onPressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
   virtual bool onReleaseKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

   cocos2d::EventListenerKeyboard* _gmlistenerKeyBoard;

   //聊天框
   ChatBox* _chatBox;

   //记录点击次数
   static int _countButton;
};
