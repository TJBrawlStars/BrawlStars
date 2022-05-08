#include "LoadingScene.h"
#pragma execution_character_set("utf-8")  

bool LoadingScene::init()
{
	if (!Layer::init())
		return false;

	//背景的设置
	_bg = Sprite::create("HelloWorld.png");
	assert(_bg != NULL);
	this->addChild(_bg);
    _bg->setPosition(kVisibleSize / 2);

	//按钮的设置
	_login_button = Button::create("CloseNormal.png");
	assert(_login_button != NULL);
	this->addChild(_login_button);
	_login_button->setPosition(kVisibleSize / 2);
	_login_button->addClickEventListener([this](Ref*)
		{
			//子节点随父节点一起淡入淡出
			this->setCascadeOpacityEnabled(true);
			//auto delay = DelayTime::create(1.f);
			auto fadeout = FadeOut::create(1.f);
			auto distory = RemoveSelf::create();
			this->runAction(Sequence::create( fadeout, distory, NULL));
		});

	auto label = Label::createWithSystemFont("登录界面", "方正姚体", 50);
	label->setPosition(kVisibleSize.x / 2, kVisibleSize.y / 2 - 200);
	this->addChild(label);

	return true;
}
