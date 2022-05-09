#include "MapInfo.h"
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
