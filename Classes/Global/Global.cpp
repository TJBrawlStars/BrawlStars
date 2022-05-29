#include <vector>
#include "Const/Const.h"


//存放英雄
//游戏结束要clear吗？
std::vector<HeroData> herodataVec;


//update leaderboard
void GameScene::updateLeaderBoard()
{
    static int overnum = 0;

    //第一个死的是2个奖杯，后over的奖杯数依次+1
    //总吃鸡数，判断over的数如果等于10，吃鸡数+1

    //主角
    if (!_heroVec[0]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(10, Rank{ 1 + overnum,0 });
            single.insert_sum(10, Rank{ 1 + overnum,0 });//吃鸡数也会自动相加吗？
        }
        //第一名
        else
        {
            single.insert(10, Rank{ 1 + overnum,1 });
            single.insert_sum(10, Rank{ 1 + overnum,1 });
        }
    }

    //机器人/其他玩家？
    if (!_heroVec[1]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(11, Rank{ 1 + overnum,0 });
            single.insert_sum(11, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(11, Rank{ 1 + overnum,1 });
            single.insert_sum(11, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[2]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(12, Rank{ 1 + overnum,0 });
            single.insert_sum(12, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(12, Rank{ 1 + overnum,1 });
            single.insert_sum(12, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[3]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(13, Rank{ 1 + overnum,0 });
            single.insert_sum(13, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(13, Rank{ 1 + overnum,1 });
            single.insert_sum(13, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[4]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(14, Rank{ 1 + overnum,0 });
            single.insert_sum(14, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(14, Rank{ 1 + overnum,1 });
            single.insert_sum(14, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[5]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(15, Rank{ 1 + overnum,0 });
            single.insert_sum(15, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(15, Rank{ 1 + overnum,1 });
            single.insert_sum(15, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[6]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(16, Rank{ 1 + overnum,0 });
            single.insert_sum(16, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(16, Rank{ 1 + overnum,1 });
            single.insert_sum(16, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[7]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(17, Rank{ 1 + overnum,0 });
            single.insert_sum(17, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(17, Rank{ 1 + overnum,1 });
            single.insert_sum(17, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[8]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(18, Rank{ 1 + overnum,0 });
            single.insert_sum(18, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(18, Rank{ 1 + overnum,1 });
            single.insert_sum(18, Rank{ 1 + overnum,1 });
        }
    }
    else if (!_heroVec[9]->alive())
    {
        ++overnum;
        if (overnum != 10)
        {
            single.insert(19, Rank{ 1 + overnum,0 });
            single.insert_sum(19, Rank{ 1 + overnum,0 });
        }
        else
        {
            single.insert(19, Rank{ 1 + overnum,1 });
            single.insert_sum(19, Rank{ 1 + overnum,1 });
        }
    }

}