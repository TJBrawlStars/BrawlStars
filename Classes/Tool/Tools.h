#pragma once

#include"cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 工具类，提供各种方法
*/
class Tools
{
public:

	/**
	* @brief 初始化一下static成员变量以便后续使用
	*/
	static void set() { kVisibleSize = cocos2d::Director::getInstance()->getVisibleSize(); }

	/**
	* @brief 提供使用九宫格精灵设置图片按钮和文字按钮的封装方法
	* @param (Vec2 position)位置
    * @param (std::string pic_name)图片路径
    * @param (std::string words)文字按钮的显示文字
    * @param (Scene* that)场景的this指针
    */
	static cocos2d::ui::Button* ButtonCreate(const cocos2d::Vec2&& position, const std::string&& pic_name, cocos2d::Node* that);
	static cocos2d::ui::Button* ButtonCreate(const std::string&& words, const cocos2d::Vec2&& position, cocos2d::Node* that);
	static cocos2d::ui::Button* ButtonCreate(const cocos2d::Vec2&& position, const std::string&& words, const std::string&& pic_name
		                                   , const std::string&& pic_name_s, cocos2d::Node* that);
	////左值版本
	//static cocos2d::ui::Button* ButtonCreate(const cocos2d::Vec2&& position, const std::string&& words, const std::string& pic_name
 //                                          , const std::string& pic_name_s, cocos2d::Node* that);
	//普通图片按钮
	static cocos2d::ui::Button* ButtonCreateN(const cocos2d::Vec2&& position, const std::string&& pic_name, cocos2d::Node* that);
	static cocos2d::ui::Button* ButtonCreateN(const cocos2d::Vec2&& position, const std::string& pic_name, cocos2d::Node* that);

	/**
	* @brief 设置layer吞没点击事件
	* @param (Scene* that)场景的this指针
	* @param (EventListenerTouchOneByOne* listener）点击listener
	*/
	static void LayerSwallow(cocos2d::EventListenerTouchOneByOne* listener, cocos2d::Layer* that);

	/**
	* @brief 设置背景
	* @param (Scene* that)场景的this指针
	* @param (const std::string&&filename)图片地址
	*/
	static cocos2d::Sprite* SetBg(const std::string&& filename, cocos2d::Node* that);
	static cocos2d::Sprite* SetBg(const std::string& filename, cocos2d::Node* that);
	static cocos2d::ui::Scale9Sprite* SetBg(cocos2d::Node* that);

	/**
	* @brief 切换场景的action的一些类型
	*/
	enum class SwitchSceneType 
	{
		Down,
		Up,
		FadeIn,
		FadeOut,
		Turn,
		//给侧边栏用的
		LeftToRight,
		RightToLeft
	};

	/**
	* @brief 切换场景
	* @param (cocos2d::Node*)添加动作的节点
	* @param (SwitchSceneType)类型
	*/
	static void SwitchScene(cocos2d::Node*, SwitchSceneType);

	/**
	* @brief 封装创建slider
	* @param (cocos2d::Node*)要添加进的节点
	*/
	static cocos2d::ui::Slider* SliderCreate(cocos2d::Vec2&& pos, std::string&& bar, std::string&& Texture, std::string&& ball, cocos2d::Node*);

	/**
	* @brief 封装创建开关Menu
	* @param (cocos2d::Node*)要添加进的节点
	* @param (cocos2d::ccMenuCallback& callback)回调函数
	*/
	static cocos2d::Menu* MenuCreate(cocos2d::Vec2&& pos,std::string&& item, std::string&& item_s
		, const cocos2d::ccMenuCallback& callback , cocos2d::Node* that);

	/**
	* @brief 封装创建Label
	* @param (cocos2d::Node*)要添加进的节点
	* @param (cocos2d::ccMenuCallback& callback)回调函数
	*/
	static cocos2d::Label* LabelCreateTTF(cocos2d::Vec2&& pos, const std::string& words, std::string&& ttf, float size, cocos2d::Node*);
	static cocos2d::Label* LabelCreateSystem(const cocos2d::Vec2& pos, const std::string& words, std::string&& ttf, float size, cocos2d::Node*);

	/**
	* @brief 封装创建精灵
	* @param (cocos2d::Node*)要添加进的节点
	*/
	static cocos2d::Sprite* SpriteCreate(const cocos2d::Vec2& pos, std::string&& filename, cocos2d::Node*);

private:

	//这里不能直接给kVisibleSize用director获取，因为全局变量在director获取visiblesize之前就已经做好赋值
	static cocos2d::Size kVisibleSize;

	Tools();

};

