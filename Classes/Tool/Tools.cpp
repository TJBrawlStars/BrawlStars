#include "Tool/Tools.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "View/LoadingScene.h"
#include "View/RoomLayer.h"

//���ﲻ��ֱ�Ӹ�kVisibleSize��director��ȡ����Ϊȫ�ֱ�����director��ȡvisiblesize֮ǰ���Ѿ����ø�ֵ
cocos2d::Size Tools::kVisibleSize = Size(0, 0);

cocos2d::ui::Button* Tools::ButtonCreate(const cocos2d::Vec2&& position, const std::string&& pic_name, cocos2d::Node* that)
{
	auto button = Button::create("ui/button.png");
	assert(button != NULL);

	button->setScale9Enabled(true);
	button->setCapInsets(Rect(5, 5, 15, 15));
	button->setPosition(position);

	auto sprite = Sprite::create(pic_name);
	assert(sprite != NULL);

	button->addChild(sprite);
	button->setContentSize(Size(sprite->getContentSize().width + 50, sprite->getContentSize().height + 25));
	sprite->setPosition(button->getContentSize() / 2);
	that->addChild(button);
	return button;
}

cocos2d::ui::Button* Tools::ButtonCreate(const std::string&& words, const cocos2d::Vec2&& position, cocos2d::Node* that)
{
	auto button = Button::create("ui/button_y.png");
	assert(button != NULL);

	button->setScale9Enabled(true);
	button->setCapInsets(Rect(5, 5, 15, 15));
	button->setPosition(position);

	auto label = Label::createWithSystemFont(words, "΢���ź�", 40);
	assert(label != NULL);
	button->setTitleLabel(label);
	button->setContentSize(Size(label->getContentSize().width + 60, label->getContentSize().height + 25));
	that->addChild(button);
	return button;
}

cocos2d::ui::Button* Tools::ButtonCreate(const cocos2d::Vec2&& position,const std::string&& words, const std::string&& pic_name, const std::string&& pic_name_s, cocos2d::Node* that)
{
	auto button = Button::create(pic_name, pic_name_s);
	assert(button != NULL);
	button->setPosition(position);
	button->setScale9Enabled(true);
	button->setCapInsets(Rect(5, 5, 15, 15));

	auto label = Label::createWithSystemFont(words, "΢���ź�", 40);
	assert(label != NULL);
	button->setTitleLabel(label);
	button->setContentSize(Size(label->getContentSize().width + 120, label->getContentSize().height + 50));
	that->addChild(button);
	return button;
}

void Tools::LayerSwallow(EventListenerTouchOneByOne* listener, cocos2d::Layer* that)
{
	listener->setSwallowTouches(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, that);
}

Sprite* Tools::SetBg(const std::string&& filename, cocos2d::Node* that)
{
	auto bg = Sprite::create(filename);
	assert(bg != NULL);
	that->addChild(bg);
	bg->setPosition(kVisibleSize / 2);
	return bg;
}

cocos2d::ui::Scale9Sprite* Tools::SetBg(cocos2d::Node* that)
{
	auto bg = Scale9Sprite::create("ui/button.png");
	assert(bg != NULL);
	that->addChild(bg);

	bg->setCapInsets(Rect(5, 5, 15, 15));
	bg->setPosition(kVisibleSize / 2);
	bg->setContentSize(kVisibleSize);
	return bg;
}

void Tools::SwitchScene(cocos2d::Node* node, SwitchSceneType type)
{
	switch (type)
	{
	case SwitchSceneType::Down:
	{
		auto move1 = MoveTo::create(0.5f, Vec2(0, 0));
		auto move2 = MoveBy::create(0.15f, Vec2(0, 75));
		auto move3 = MoveBy::create(0.15f, Vec2(0, -75));
		node->setPosition(0, kVisibleSize.height);
		node->runAction(Sequence::create(move1, move2, move3, NULL));
		break;
	}
	case SwitchSceneType::Up:
	{
		auto distory = RemoveSelf::create();
		auto move = MoveTo::create(0.5f, Vec2(0, kVisibleSize.height));
		auto wait = DelayTime::create(0.2f);
		node->runAction(Sequence::create(wait, move, distory, NULL));
		break;
	}
	case SwitchSceneType::FadeOut:
	{
		//�ӽڵ��游�ڵ�һ���뵭��
		node->setCascadeOpacityEnabled(true);
		auto delay = DelayTime::create(0.3f);
		auto fadeout = FadeOut::create(1.f);
		auto distory = RemoveSelf::create();
		node->runAction(Sequence::create(delay, fadeout, distory, NULL));
		break;
	}
	case SwitchSceneType::FadeIn:
	{
		//�ӽڵ��游�ڵ�һ���뵭��
		node->setCascadeOpacityEnabled(true);
		//Ҫ�����ýڵ�͸���ſ�����Ч��
		node->setOpacity(0);
		auto delay = DelayTime::create(0.3f);
		auto fadein = FadeIn::create(1.f);
		node->runAction(Sequence::createWithTwoActions(delay, fadein));
		break;
	}
	case SwitchSceneType::Turn:
	{
		break;
	}
	}
}

cocos2d::ui::Slider* Tools::SliderCreate(cocos2d::Vec2&& pos, std::string&& bar, std::string&& Texture, std::string&& ball, cocos2d::Node* that)
{
	auto slider = Slider::create();
	that->addChild(slider);
	slider->loadBarTexture(bar);
	slider->loadProgressBarTexture(Texture);
	slider->loadSlidBallTextures(ball);
	slider->setPosition(pos);
	slider->setPercent(100);
	return slider;
}

cocos2d::Menu* Tools::MenuCreate(cocos2d::Vec2&& pos, std::string&& item, std::string&& item_s, const ccMenuCallback& callback , cocos2d::Node* that)
{
	auto sound_menuitem = MenuItemImage::create(item, item);
	auto sound_menuitem_s = MenuItemImage::create(item_s, item_s);
	auto sound_menutoggle = MenuItemToggle::createWithCallback(callback, sound_menuitem, sound_menuitem_s, NULL);
	auto soundmenu = Menu::create(sound_menutoggle, NULL);
	assert(soundmenu != NULL);
	that->addChild(soundmenu);
	soundmenu->setPosition(pos);
	return soundmenu;
}

cocos2d::Label* Tools::LabelCreateTTF(cocos2d::Vec2&& pos, std::string&& words, std::string&& ttf ,float size, Node* that)
{
	auto label = Label::createWithTTF(words, ttf, size);
	assert(label != NULL);
	that->addChild(label);
	label->setPosition(pos);
	return label;
}

cocos2d::Label* Tools::LabelCreateSystem(cocos2d::Vec2&& pos, std::string&& words ,std::string&& ttf, float size, Node* that)
{
	auto label = Label::createWithSystemFont(words, ttf, size);
	assert(label != NULL);
	that->addChild(label);
	label->setPosition(pos);
	return label;
}



