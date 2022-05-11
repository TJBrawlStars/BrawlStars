#pragma once
#include "Item.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Const/Const.h"
#include "Tool/DiamondBuff.h"

/**
* @author:张靖凯
* @实现宝箱类
*/
class TreasureBox : public Item
{
public:
	CREATE_FUNC(TreasureBox);

	/**
	* @初始化、打开宝箱
	*/
	bool virtual init() override;
	void openBox();


	/**
	* @fn createBox
	* @brief 创建宝箱
	*/
	TreasureBox* createBox();

	//没用！！！
	//cocos2d::Vec2 getBoxPos() {return _boxPos;};
	//void setBoxPos(cocos2d::Vec2 position);

	TreasureBox(const int& maxBoxHealthPoint = kmaxBoxHealthPoint) :_maxHealthPoint(maxBoxHealthPoint) {_healthPoint = _maxHealthPoint;};

	/**
	* @fn initialzeBloodStrip
	* @brief 初始化血条
	*/
	void initialzeBloodStrip(const int maxBoxHealthPoint);

	/**
	* @fn deductHP
	* @brief 减少血量
	*/
	int deductHP(int deductPoint);

	int getHP() const noexcept { return _healthPoint; }

	/**
    * @fn isInExistPhysicalItem
    * @brief 判断位置处是否有物理引擎
    */
	static bool isInExistPhysicalItem();
protected:
	//出过bug，别放在初始化的位置！！！也没必要再用
	////宝箱位置
	//cocos2d::Vec2 _boxPos;

    //血条
	const int _maxHealthPoint;
	int _healthPoint;

private:
	cocos2d::ui::LoadingBar* _bloodStrip = cocos2d::ui::LoadingBar::create(Path::kbloodStrip);  ///< the blood strip
};
