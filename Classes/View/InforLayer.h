#pragma once

#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 个人信息场景
*/
class InforLayer :public cocos2d::Layer
{
public:

	CREATE_FUNC(InforLayer);

	/**
    * @brief 标志有什么类型的信息
    */
	enum class Information
	{
		Name,
		Cup,
		Money,
		MaxRank,
	};

	/**
    * @brief 更名info方法
    */
	void Change(const std::string& newinfo, Information infoType);

private:

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) { return true; }

	InforLayer() :kVisibleSize(cocos2d::Director::getInstance()->getVisibleSize())
		, _bg(NULL), _back(NULL), _profile(NULL), _change_name(NULL), kInfos(3) {};

	/**
    * @brief 提供创建info标签的方法（一个标题+一个数字）
	* @param (Information info)标题
	* @param (const int num)初始显示值
    */
	void setInfo(Information infoType, const std::string&& info = "");

	/**
	* @brief 文本框点击事件
	*/
	void TextFieldEvent(Ref* pSender, cocos2d::ui::TextField::EventType type);

private:

	const cocos2d::Size kVisibleSize;

	//设置画面背景
	cocos2d::ui::Scale9Sprite* _bg;

	//返回按钮
	cocos2d::ui::Button* _back;

	//头像
	cocos2d::ui::Button* _profile;

	//存下可改变的info数字
	cocos2d::Vector<cocos2d::Label*> _infomation;

	//更改名字按钮
	cocos2d::ui::Button* _change_name;

	//文本框
	cocos2d::ui::TextField* _text;

	//头像个数，在初始化的地方改
	const int kInfos;

};
