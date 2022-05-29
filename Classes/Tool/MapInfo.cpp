//2151396 ÕÅ¾¸¿­

#include "MapInfo.h"
#include "Const/Const.h"
USING_NS_CC;

void MapInfo::setCollisionBoard()
{
    //_obstacleLayer->setVisible(false);

    for (int i = 0; i < _mapTiledNum.width; i++)
    {
        for (int j = 0; j < _mapTiledNum.height; j++)
        {
            if (_obstacleLayer->getTileGIDAt(Vec2(i, j)) != 0)
            {
                _collisionBoard[i][_mapTiledNum.height - 1 - j] = true;
            }
        }
    }
}

Vec2 MapInfo::randomPos()
{
    const int posX = cocos2d::random(32, maxWidth - 32);
    const int posY = cocos2d::random(32, maxHeight - 32);

    Vec2 pos = Vec2(posX, posY);
    return Vec2(pos);
}
