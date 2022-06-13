//2151396 �ž���

#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include "cocos2d.h"
#include "Const/Const.h"

class GameScene;

/**
* @brief ��ʱ��
* @���캯���Ϳ�ʼ��ʱ
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
    * ������ʱ
    */
    inline void restart();


    /**
    * ��¼��ʱ
    * @return ����ms��
    */
    inline double elapsed(bool restart = false);

    /**
     * ��ӡʱ�䲢������ʱ��
     * @param tip ��ʾ
     */
    void rlog(const std::string& tip);


    /**
    * @brief ��ӡʱ��
    * @param reset ���֮���Ƿ�������ʱ����true������false������
    * @param unit_ms true��ms��false��s
    * @param tip �����ʾ
    * @param kill ���֮���Ƿ��˳�����true�˳���false���˳�
    *
    * �����޸�
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