/**
* @author 张靖凯
* 初始化英雄
*/
#include"cocos2d.h"
#include "View\GameScene.h"
#include "Const/Const.h"
#include "Hero/Robot.hpp"
#include <sstream>

extern std::vector<HeroData> herodataVec;

void GameScene::addHeroPlayer() 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化位置对象层
	initObjPosition();
	std::vector<int> tenRandVector = randTenNumberVec(10);


	//将第一个设置为主角
	for (int i = 0; i < 1; i++)
	{
		//初始化操作
		Hero* player = nullptr;
		
		std::istringstream temp(herodataVec[i].name_isRobot);
		std::string heroname;
		std::string isRobot;
		temp >> heroname;
		temp >> isRobot;

		if (heroname == "Beiya")
		{
			if (isRobot == "true")
				/*player = Robot<Beiya>::createRobot()*/;
			else if(isRobot == "false")
			{
				player = Beiya::createBeiya();
			}

			_heroVec.push_back(player);
			player->setPosition(_tenPosition[tenRandVector[i]]);
			this->addChild(player, kHeroPriority, i+10);
		}
		///补else if其他类型的角色
	}


	//设置主角
	//_player = dynamic_cast<Hero*>(this->getChildByTag(10));
	_player = _heroVec[0];

}