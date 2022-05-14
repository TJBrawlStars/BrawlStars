#pragma once
#include "cocos2d.h"
#include "Const/Const.h"

class MapInfo
{
public:
    //地图
    cocos2d::TMXTiledMap* _map;
    //碰撞层(有bug)
    cocos2d::TMXLayer* _obstacleLayer;
    //地图方块数量
    cocos2d::Size _mapTiledNum;
    //单个格子大小（有bug！！！!）
    cocos2d::Size _tiledSize;
    //碰撞瓦片（左下角的瓦片坐标,如果是碰撞层则坐标为true）//（暂时用不到，后续可能）
    TileVector _collisionBoard = TileVector(_mapTiledNum.width, std::vector<bool>(_mapTiledNum.height, false));
public:
    void setCollisionBoard();
    //随机产生一个位置
    static cocos2d::Vec2 randomPos();
};