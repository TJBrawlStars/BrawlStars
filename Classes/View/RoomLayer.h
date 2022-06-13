#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"Tool/Member.h"

class Member;

/**
* @brief 房间场景
*/
class RoomLayer :public cocos2d::Layer
{
public:

	CREATE_FUNC(RoomLayer);

	/**
    * @brief 成员的点击函数
    */
	void menuCloseCallback(Ref* pSender);

	/**
    * @brief 设置自己的角色
    */
	static void setSelf(const std::string& filename);

private:

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	RoomLayer() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _choose_hero(NULL), _start(NULL), _back(NULL), _vs(NULL), _robots(NULL), _member(), _self(NULL), _current(NULL) {};

	~RoomLayer() { _that = NULL; }

	/**
	* @brief 设置9个房间成员框，包括一个房主框和5个+框
	*/
	void MemberCreate();

	/**
    * @brief 设给机器人随机英雄
    */
	std::string RandomHero(const std::vector<std::string>&);

	/**
	* @brief 9个+框
	*/
	void PlusMemberCreate();

	/**
	* @brief 设置选择机器人或者玩家按钮时其他按钮不能点还有各种共同操作
	*/
	void SetButton();

	/**
	* @brief 传递英雄数据给游戏场景
	*/
	void SetHero();

private:

	const cocos2d::Size kVisibleSize;

	static RoomLayer* _that;

	//登录画面背景
	cocos2d::ui::Scale9Sprite* _bg;

	//选择hero按钮
	cocos2d::ui::Button* _choose_hero;

	//开始对战按钮
	cocos2d::ui::Button* _start;
	
	// 返回按钮
	cocos2d::ui::Button* _back;
	
	//vs标识
	cocos2d::Label* _vs;

	//自动补全机器人按钮
	cocos2d::ui::Button* _robots;

	Member _member;

	std::vector<HumanData> _humandata;

	//成员
	cocos2d::Vector<cocos2d::MenuItemToggle*> _figures;

	//self
	cocos2d::ui::Button* _self;

	//当前操作成员
	cocos2d::MenuItemToggle* _current;

};

