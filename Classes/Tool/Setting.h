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

    /*-----------------------------------------------背景音*/
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

    /**
    * @brief 是否播放背景音
    */
    bool isSound() { return _sound; }

    /*-----------------------------------------------音效*/
    /**
    * @brief 播放指定音效
    */
    void GoSoundEffect(std::string filename);

    /**
    * @brief 设置音效是否播放
    */
    void SoundEffectSet(const bool set);

    /**
    * @brief 设置音效百分比
    */
    void SoundEffectPercentSet(const int persent);

    /**
    * @brief 是否播放音效
    */
    bool isSoundEffect() { return _sound_effect; }

private:

    static Setting* instance;

    bool _sound;

    bool _sound_effect;

    CocosDenshion::SimpleAudioEngine* _sound_engine = CocosDenshion::SimpleAudioEngine::getInstance();

private:

    Setting() :_sound(true), _sound_effect(true) {};

};

