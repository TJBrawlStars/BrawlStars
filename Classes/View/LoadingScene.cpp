#include "LoadingScene.h"
USING_NS_CC;
using namespace ui;
#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include "Tool/Setting.h"
#include "Tool/Tools.h"
#include "Tool/Data.h"
#pragma execution_character_set("utf-8")  

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	//声音开始
	Setting::getInstance()->GoSound("audio/main.mp3");
	
	//设置吞噬点击事件(不知道为什么前两句加到封装里第二句等号会报错)
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoadingScene::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景的设置
	_bg = Tools::SetBg("ui/loadingBg.jpg", this);

	//未登录的要登陆
	if (!Setting::getInstance()->isLogin())
	{
		//输入id文本框
		_text = Tools::TextCreate(kVisibleSize / 2, "点击这里输入id(2字符内,未知的id信息会在本设备新建账号)", 3, this);
		_text->addEventListener(CC_CALLBACK_2(LoadingScene::TextFieldEvent, this));
		_text->setColor(Color3B::BLACK);
		//加个底框，看的清楚点
		auto bg = Scale9Sprite::create("ui/button.png");
		assert(bg);
		bg->setCapInsets(Rect(5, 5, 15, 15));
		bg->setContentSize(Size(_text->getContentSize().width + 30, (_text->getContentSize().height + 15)));
		bg->setPosition(kVisibleSize / 2);
		this->addChild(bg);
		bg->setName("bg");

		//登录按钮
		_login_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height * 0.3f)
			, "登      录", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
		//这边真要登录的话就新写一个函数叭
		_login_button->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED && _id != "")
				{
					Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
					auto distory = RemoveSelf::create();
					_login_button->runAction(distory);
					_text->runAction(distory->clone());
					this->removeChildByName("bg");

					//感觉这个路径release版本要改一下啊，然后还要加一个输入
					PlistData::addDate(_id, "../Resources/Data/data" + _id + ".plist");

					MainScene::GetMainScene()->Load();
					Setting::getInstance()->SetLogin(true);
					LoadGame();
				}
			});
	}
	else
		LoadGame();

	CCLOG("LoadingScene finish");
	return true;
}

void LoadingScene::LoadGame()
{
	/*-----------------------------------------------------------------------------------开始游戏按钮*/
	_start_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 150)
		, "开始游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_start_button->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Tools::SwitchScene(this, Tools::SwitchSceneType::FadeOut);
			}
		});

	/*-----------------------------------------------------------------------------------退出按钮*/
	_exit_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 250)
		, "结束游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_exit_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				Setting::getInstance()->GoSoundEffect("audio/click_effect.mp3");
				Director::getInstance()->end();
			}
		});

}

void LoadingScene::TextFieldEvent(Ref* pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		dynamic_cast<TextField*>(pSender)->setString("|");
		break;
	}
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		auto item = dynamic_cast<TextField*>(pSender);
		_id = item->getString().substr(1, item->getString().length() - 1);
		item->setString(_id);
		break;
	}
	default:
		break;
	}
}

bool LoadingScene::onTouchBegan(Touch*, Event*)
{
	//这里要设置true这个loading层才会吞没点击事件，标记坑
	return true;
}

