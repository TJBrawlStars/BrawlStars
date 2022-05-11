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

	cocos2d::Vec2 getBoxPos() {return _boxPos;};
	void setBoxPos(cocos2d::Vec2 position) = delete;//不能随便动

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
protected:
	//宝箱位置
	cocos2d::Vec2 _boxPos;

    //血条
	const int _maxHealthPoint;
	int _healthPoint;

private:
	cocos2d::ui::LoadingBar* _bloodStrip = cocos2d::ui::LoadingBar::create(Path::kbloodStrip);  ///< the blood strip
};
