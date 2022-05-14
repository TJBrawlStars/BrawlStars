#include "Setting.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

Setting* Setting::instance = NULL;

Setting* Setting::getInstance()
{
	if (instance == NULL)
	{
		instance = new Setting();
		auto a = instance->_sound;
		//ÈÝ´í´¦Àí
		if (instance)
		{
			instance->autorelease();
			instance->retain();
		}
		else
		{
			CC_SAFE_DELETE(instance);
			instance = NULL;
		}
	}
	return instance;
}

void Setting::GoSound(std::string filename)
{
	_sound_engine->playBackgroundMusic(filename.c_str(), true);
}

void Setting::SoundSet(const bool set)
{
	_sound = set;
	if (set)
		_sound_engine->resumeBackgroundMusic();
	else
		_sound_engine->pauseBackgroundMusic();
}

void Setting::StopSound()
{
	_sound_engine->getInstance()->stopBackgroundMusic();
}

void Setting::SoundPercentSet(const int persent)
{
	_sound_engine->getInstance()->setBackgroundMusicVolume(persent * 0.01f);
}

void Setting::GoSoundEffect(std::string filename)
{
	if (_sound_effect != false)
		_sound_engine->playEffect(filename.c_str());
}

void Setting::SoundEffectSet(const bool set)
{
	_sound_effect = set;
}

void Setting::SoundEffectPercentSet(const int persent)
{
	_sound_engine->getInstance()->setEffectsVolume(persent * 0.01f);
}
