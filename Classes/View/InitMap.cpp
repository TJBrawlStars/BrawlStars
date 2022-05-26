/**
* @author 张靖凯
* @brief 初始化地图
*/
#include"cocos2d.h"
#include "View\GameScene.h"
#include "Const/Const.h"
#include <algorithm>
using namespace std;
USING_NS_CC;

void GameScene::addMap(int chooseNum)
{
    ////初始化各个变量！！！！！！！！
    //const int mapChooseNum = random(1, 3);
    string mapChooseStr;
    if (chooseNum == 1)
        mapChooseStr = Path::map1;
    else if (chooseNum == 2)
        mapChooseStr = Path::map2;
    else if (chooseNum == 3)
        mapChooseStr = Path::map3;

    _mapinfo._map = TMXTiledMap::create(mapChooseStr);
    _mapinfo._map->setAnchorPoint(Vec2::ZERO);
    _mapinfo._map->setPosition(Vec2::ZERO);
    this->addChild(_mapinfo._map, kMapPriority);

    //让障碍层显示在global
    _mapinfo._obstacleLayer = _mapinfo._map->getLayer("1");
    _mapinfo._obstacleLayer->setGlobalZOrder(kTMXlayer);
    _mapinfo._obstacleLayer = _mapinfo._map->getLayer("2");
    _mapinfo._obstacleLayer->setGlobalZOrder(kTMXlayer);
    _mapinfo._obstacleLayer = _mapinfo._map->getLayer("3");
    _mapinfo._obstacleLayer->setGlobalZOrder(kTMXlayer);

    //草丛不能这样哦~~~~
    //_mapinfo._obstacleLayer = _mapinfo._map->getLayer("4");
    //_mapinfo._obstacleLayer->setGlobalZOrder(kTMXlayer);
    // 
    //地图方块数量
    _mapinfo._mapTiledNum = _mapinfo._map->getMapSize();
    //单个格子大小
    _mapinfo._tiledSize = _mapinfo._map->getTileSize();
    //初始化结束
}


Vec2 GameScene::tiledCoordFromPosition(Vec2 position)
{
    int mpx = _mapinfo._tiledSize.width * _mapinfo._mapTiledNum.width;
    int mpy = _mapinfo._tiledSize.height * _mapinfo._mapTiledNum.height;
    //opengl坐标
    Vec2 posInMap = Vec2(position.x, position.y);
    //UI像素坐标
    Vec2 posInMapUI = Vec2(position.x, mpy - position.y);

    //转换成瓦片坐标
    int x = posInMapUI.x / _mapinfo._tiledSize.width;
    int y = posInMapUI.y / _mapinfo._tiledSize.height;

    return Vec2(x, y);
}

Vec2 GameScene::destPos(Point position)
{
    //屏幕大小
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //地图大小
    Size mapSize = Size(_mapinfo._mapTiledNum.width * _mapinfo._tiledSize.width, _mapinfo._mapTiledNum.height * _mapinfo._tiledSize.height);

    //主角坐标 
    Point playerPos = position;

    //如果主角坐标小于屏幕一半，则取屏幕中点坐标
    //算法
    float x = std::max(playerPos.x, visibleSize.width / 2);
    float y = std::max(playerPos.y, visibleSize.height / 2);

    x = std::min(x, mapSize.width - visibleSize.width / 2);
    y = std::min(y, mapSize.height - visibleSize.height / 2);

    //目标点
    return Vec2(x, y);
}


Vec2 GameScene::randomPosWithoutBarrier()
{
    float x = cocos2d::random(32, maxWidth - 32);
    float y = cocos2d::random(32, maxHeight - 32);

    if (!isGrassExist(Point(x, y)) && !isBarrierExist(Point(x, y)))
        return Vec2(x, y);
    else
        return randomPosWithoutBarrier();
}

void GameScene::setViewPointByPlayer(Point position)
{
    //精灵不存在就退出
    if (_player == nullptr)
        return;

    //屏幕大小
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //目标点
    Vec2 destPosition = destPos(position);
    //屏幕中点
    Vec2 centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);

    //屏幕中点和所要移动的目标点之间的距离
    Vec2 viewPos = centerPos - destPosition;
    //log("destPos.x=%f", destPosition.x);
    this->setPosition(viewPos);
}



//初始化地图的10个位置
void GameScene::initObjPosition()
{
    int i = 0;
    auto group = _mapinfo._map->getObjectGroup("initobj");
    ValueVector initobjPos = group->getObjects();
    for (auto posi : initobjPos) 
    {
        ValueMap& dict = posi.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();

        //把对象代表的地址放入容器
        _tenPosition.insert(std::pair<int, Vec2>(i,Vec2(x,y)));
        i++;
    }
}


//n个位置产生(0~9）
std::vector<int> GameScene::randTenNumberVec(int Num)
{
    vector<int> temp;
    for (int i = 0; i < Num; ++i)
    {
        temp.push_back(i);
    }
    random_shuffle(temp.begin(), temp.end());
    
    return temp;
}
