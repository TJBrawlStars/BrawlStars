#include "PauseScene.h"
USING_NS_CC;
using namespace ui;
#define NDEBUG
#include<cassert>
#include"Tool/Tools.h"
#include"MainScene.h"
#include"Tool/Setting.h"
#include"Tool/SceneManager.h"
#pragma execution_character_set("utf-8")  

//Scene* PauseScene::_scene = NULL;
//std::string PauseScene::_outputfile = "";

bool PauseScene::init()
{
	if (!Scene::init())
		return false;

	this->setTag(777);
	_bg = Tools::SetBg(this);

	//readme
	_readme = Tools::LabelCreateSystem(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.7f), "ÒÑÔÝÍ£", "Î¢ÈíÑÅºÚ", 70, this);

	//µã»÷°´Å¥
	_resume = Tools::ButtonCreate("»Ö¸´", kVisibleSize / 2, this);
	_resume->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Setting::getInstance()->SoundSet(true);
				SceneManager::getInstance()->changeScene(SceneManager::EnumSceneType::en_Min, 2);
			}
		});

	return true;
}

//bool PauseScene::onTouchBegan(cocos2d::Touch*, cocos2d::Event*)
//{
//
//	return true;
//}

//void PauseLayer::Capture(Scene* scene)
//{
//	CCLOG("screencut");
//	_scene = scene;
//	utils::captureScreen(CC_CALLBACK_2(PauseLayer::AfterCapture, _scene), "ScreenShot.png");
//}

//void PauseLayer::AfterCapture(bool succeed, const std::string& outputFile)
//{
//	if (succeed)
//	{
//		assert(_scene);
//		CCLOG("% s", outputFile.c_str());
//		auto layer = PauseLayer::create();
//		Tools::SwitchScene(layer, Tools::SwitchSceneType::Down);
//		_scene->addChild(layer);
//		_outputfile = outputFile;
//		assert(_outputfile != "");
//	}
//	else
//		CCLOG("shotcut fail");
//}
