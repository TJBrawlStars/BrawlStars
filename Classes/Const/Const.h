#pragma once
#include "cocos2d.h"

//从左下角（0,0）开始的瓦片地图
typedef std::vector<std::vector<bool>> TileVector;
const int maxWidth = 32 * 75;
const int maxHeight = 32 * 75;

//宝箱
const int kmaxBoxHealthPoint = 3360;

//物理引擎设置了Tag和Name，方便碰撞检测接口
//Tag
const int kBarrierTag = 0;
const int kBoxTag = 1;
const int kDiamondTag = 2;

//Buff的值
const int kBuffAttack = 100;
const int kBuffHealth = 1000;

namespace Name
{
	static const std::string kBarrier = "Barrier";
	static const std::string kTreasureBox = "TreasureBox";
	static const std::string kDiamond = "Diamond";
}

//general Priority
const int kMapPriority = 0;
const int kHeroPriority = 1;
const int kBarrierPriority = 2;//障碍物物理引擎的优先级
const int kBoxPriority = 3;
const int kDiamondPriority = 4;

//global Priority （总是比general Priority高的！）
const int kTMXlayer = 100;

//文件路径
namespace Path
{
	static const std::string BoxClose = "Box/BoxClose.png";
	static const std::string BoxOpen = "Box/BoxOpen.png";
	static const std::string Diamond = "Box/diamond.png";

	static const std::string kbloodStrip = "bloodStrip.png";
}

