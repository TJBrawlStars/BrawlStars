//2151396 张靖凯

#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "cocos2d.h"
#include "Const/Const.h"

class GameScene;

/**
* @brief 计时器
* @构造函数就开始计时
*/

class MyTimer : public cocos2d::Node
{
public:
    //CC_SYNTHESIZE(cocos2d::Sprite*, _timerInfoBG, TimerInfoBG);
    //CC_SYNTHESIZE(cocos2d::Label*, _timerInfo, TimerInfo)
    CREATE_FUNC(MyTimer);

    MyTimer() :_name() 
    {
        restart();
        createUI(); 
    }

    explicit MyTimer(const std::string& name) :_name(name + ":") 
    { 
        restart();
        createUI();
    }

    std::string getHour() { return std::to_string(static_cast<int>(elapsed() / 1000.0) / 3600); }
    std::string getMinute() { return std::to_string(static_cast<int>(elapsed() / 1000.0) / 60); }
    std::string getSecond() { return std::to_string(static_cast<int>(elapsed() / 1000.0) % 60); }

    /**
    * 启动计时
    */
    inline void restart();


    /**
    * 记录计时
    * @return 返回ms数
    */
    inline double elapsed(bool restart = false);

    /**
     * 打印时间并重启计时器
     * @param tip 提示
     */
    void rlog(const std::string& tip);


    /**
    * @brief 打印时间
    * @param reset 输出之后是否重启计时器，true重启，false不重启
    * @param unit_ms true是ms，false是s
    * @param tip 输出提示
    * @param kill 输出之后是否退出程序，true退出，false不退出
    *
    * 做了修改
    */
    void log(bool reset = false, const std::string& tip = "", bool unit_ms = false, bool kill = false);

    void createUI();

    //void updatePosition();

    cocos2d::Sprite* getMyTimerInfoBG() { return _timerInfoBG; }
    cocos2d::Label* getMyTimerInfo() { return _timerInfo; }

   // void update(float dlt = 0.01f);
private:
    std::chrono::steady_clock::time_point _start_time;
    std::chrono::steady_clock::time_point _end_time;
    std::string _name;

    cocos2d::Sprite* _timerInfoBG;
    cocos2d::Label* _timerInfo;
};