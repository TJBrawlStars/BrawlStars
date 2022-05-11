/**
* @author ÕÅ¾¸¿­
* ³õÊ¼»¯Ó¢ÐÛ
*
*/
#include"cocos2d.h"
#include "View\GameScene.h"
#include "Const/Const.h"
#

void GameScene::addHeroPlayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_player = Beiya::createBeiya();
	_player->setPosition(Vec2(100,100));

	this->addChild(_player, kHeroPriority);
}