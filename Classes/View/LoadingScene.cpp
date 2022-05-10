#include "LoadingScene.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "Tool/SceneManager.h"
#include "Tool/Setting.h"
#include "Tool/Tools.h"
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

	//按钮的设置
	_login_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 150)
		, "开始游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_login_button->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
				Tools::SwitchScene(this, Tools::SwitchSceneType::FadeOut);
		});

	//退出按钮
	_exit_button = Tools::ButtonCreate(Vec2(kVisibleSize.width / 2, kVisibleSize.height / 2 - 250)
		, "结束游戏", "ui/loadingButton.png", "ui/loadingButton_s.png", this);
	_exit_button->addTouchEventListener([this](Ref*, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
				Director::getInstance()->end();
		});

	return true;
}

//弃用

//Button* LoadingScene::SetButton(const Vec2&& pos, const std::string&& title, const std::string&& pic1, const std::string&& pic2)
//{
//	auto button = Button::create(pic1, pic2);
//	assert(button != NULL);
//	button->setPosition(pos);
//	button->setScale9Enabled(true);
//	button->setCapInsets(Rect(5, 5, 15, 15));
//	auto label = Label::createWithSystemFont(title, "微软雅黑", 40);
//	assert(label != NULL);
//	button->setTitleLabel(label);
//	button->setContentSize(Size(label->getContentSize().width + 120, label->getContentSize().height + 50));
//	this->addChild(button);
//	return button;
//}

bool LoadingScene::onTouchBegan(Touch*, Event*)
{
	//这里要设置true这个loading层才会吞没点击事件，标记坑
	return true;
}

