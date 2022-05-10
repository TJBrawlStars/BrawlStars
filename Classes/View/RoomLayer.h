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


private:

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	RoomLayer() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _choose_hero(NULL), _start(NULL), _back(NULL), _vs(NULL), _robots(NULL), _member() {};

	//弃用

	//**
 //   * @brief 设置按钮并add进场景,有两个重载版本
 //   * @param (Vec2 position)位置
 //   * @param (std::string pic_name)图片路径
	//* @param (std::string words)文字按钮的显示文字
 //   */
	//cocos2d::ui::Button* ButtonCreate(const cocos2d::Vec2&& position, const std::string&& pic_name);
	//cocos2d::ui::Button* ButtonCreate(const std::string&& words, const cocos2d::Vec2&& position);

	/**
	* @brief 设置6个房间成员框，包括一个房主框和5个+框
	*/
	void MemberCreate();

	/**
	* @brief 5个+框
	*/
	void PlusMemberCreate();

private:

	const cocos2d::Size kVisibleSize;

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

	////敌方人数
	//Member _enemy;

	////我方人数
	//Member _our;

	Member _member;

	//成员
	cocos2d::Vector<cocos2d::MenuItemToggle*> _figures;

};

