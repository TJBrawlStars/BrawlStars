#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

/**
* @brief 设置控制器
*/
class Setting :public cocos2d::Ref
{
public:

    static Setting* getInstance();

    /**
    * @brief 播放指定背景音乐
    */
    void GoSound(std::string filename);

    /**
    * @brief 设置背景声音是否播放
    */
    void SoundSet(const bool set);

    /**
    * @brief 停止当前背景音
    */
    void StopSound();

    /**
    * @brief 设置背景声音百分比
    */
    void SoundPercentSet(const int persent);

private:

    static Setting* instance;

    bool _sound;

    CocosDenshion::SimpleAudioEngine* _sound_engine = CocosDenshion::SimpleAudioEngine::getInstance();

private:

    Setting() :_sound(true) {};

};

