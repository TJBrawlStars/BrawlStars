#include <vector>
#include "Const/Const.h"
#include"Tool/LeaderBoard.hpp"
#include"View/GameScene.h"
#include"Tool/Data.h"

std::vector<HeroData> herodataVec;

LeaderBoard<std::string, Rank> single;

LeaderBoard<std::string, Rank> all;

//update leaderboard
void GameScene::updateLeaderBoard()
{
    
   int overnum = 0;
    std::vector<std::string> robot = { "robot1","robot2","robot3","robot4","robot5","robot6","robot7","robot8","robot9"};

    
    
    if (_heroVec[0]->alive() == false)
    {
        ++overnum;
        for (int j = 1; j < 10; ++j)
        {
            if (_heroVec[j]->alive() == false)
                ++overnum;
        }
        
        //吃鸡
        if (overnum == 10)
            single.insert(PlistData::getDataByType(PlistData::DataType::ID), Rank{ 1,overnum });
        else if (overnum == 1)
        {
            for (int i = 0; i < 9; ++i)
            {
                single.insert(robot[i], Rank{ 1,i+2 });
            }
            single.insert(PlistData::getDataByType(PlistData::DataType::ID), Rank{ 0,1 });
        }
        else
        {
            single.insert(PlistData::getDataByType(PlistData::DataType::ID), Rank{ 0,overnum });
            //假如说他原来是第六名的话,这一块需要改一下，就是如果他是中间死的话得倒着赋值
            //如果是第六名，10.9.8.7.（6）.5.4.3.2.1
            int count = 1;
            for (int i = 0; i < 9; ++i)
            {
                single.insert(robot[i], Rank{ 1,count++});
                if (count == overnum)
                    ++count;
            }
        }
        SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_SettlementScene);
    }
}

