#pragma once
#include "cocos2d.h"
#include "Const/Const.h"

/**
* @class Item
* @brief 物品类
*/
class Item : public cocos2d::Node
{
public:
	void bindSprite(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getSprite();

	/**
	* @fn generatePhysicalBody
	* @brief 物体产生物理属性
	* @param tag and name
	*/
	void generatePhysicalBody(std::string message, int itemTag);

protected:
	//物体本身
	cocos2d::Sprite* _sprite;
};
