#include "MainScene.h"
#pragma execution_character_set("utf-8")  

bool MainScene::init()
{
	if (!Scene::init())
		return false;

	////设置背景
	//_bg = Sprite::create("");
	//assert(_bg != NULL);
	//this->addChild(_bg);
	//_bg->setPosition(kVisibleSize / 2);

	//设置loading界面
	if (SceneManager::getInstance()->isFirst())
	{
		_loading = LoadingScene::create();
		assert(_loading != NULL);
		this->addChild(_loading, 100);
	}

	////各种按钮的实现
	//_menu_button = ButtonCreate();
	//_menu_button->addClickEventListener([](Ref*)
	//	{
	//		//这里塞一个层，层上有各种按钮
	//	});
	//_info_button= ButtonCreate();
	//_info_button->addClickEventListener([](Ref*)
	//	{
	//		//弹出个人信息显示层
	//	});
	_play_button = Button::create("CloseNormal.png");
	_play_button->setPosition(kVisibleSize / 2);
	this->addChild(_play_button);
	_play_button->addClickEventListener([this](Ref*)
		{
			_room = RoomLayer::create();
			_room->setPosition(Vec2(0,0));
			assert(_room);
			this->addChild(_room);
		});

	////主界面显示的人物
	//_figure = Sprite::create();
	//assert(_figure != NULL);
	//_figure->setPosition(kVisibleSize / 2);
	//this->addChild(_figure);

	auto label = Label::createWithSystemFont("主界面", "方正姚体", 50);
	label->setPosition(kVisibleSize.x / 2, kVisibleSize.y / 2 - 100);
	this->addChild(label);


	return true;
}

Button* MainScene::ButtonCreate(Vec2 position, std::string pic_name1, std::string pic_name2)
{
	assert(position.x<0 || position.x>kVisibleSize.x || position.y<0 || position.y>kVisibleSize.y);

	decltype(Button::create()) button;
	if (pic_name2 == "")
		button = Button::create(pic_name1);
	else
		button = Button::create(pic_name1, pic_name2);

	assert(button != NULL);

	button->setPosition(position);
	this->addChild(button);
	return button;
}
