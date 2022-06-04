#include "Tool/Tools.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include "View/LoadingScene.h"
#include "View/RoomLayer.h"
#pragma execution_character_set("utf-8")  

//这里不能直接给kVisibleSize用director获取，因为全局变量在director获取visiblesize之前就已经做好赋值
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

	auto label = Label::createWithSystemFont(words, "微软雅黑", 40);
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

	auto label = Label::createWithSystemFont(words, "微软雅黑", 40);
	assert(label != NULL);
	button->setTitleLabel(label);
	button->setContentSize(Size(label->getContentSize().width + 120, label->getContentSize().height + 50));
	that->addChild(button);
	return button;
}

cocos2d::ui::Button* Tools::ButtonCreateN(const cocos2d::Vec2&& position, const std::string&& pic_name, cocos2d::Node* that)
{
	auto button = Button::create(pic_name);
	assert(button != NULL);
	that->addChild(button);
	button->setPosition(position);
	return button;
}

cocos2d::ui::Button* Tools::ButtonCreateN(const cocos2d::Vec2&& position, const std::string& pic_name, cocos2d::Node* that)
{
	auto button = Button::create(pic_name);
	assert(button != NULL);
	that->addChild(button);
	button->setPosition(position);
	return button;
}

void Tools::LayerSwallow(EventListenerTouchOneByOne* listener, cocos2d::Layer* that)
{
	listener->setSwallowTouches(true);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, that);
}

cocos2d::Sprite* Tools::SetBg(const std::string&& filename, cocos2d::Node* that)
{
	auto bg = Sprite::create(filename);
	assert(bg != NULL);
	that->addChild(bg);
	bg->setPosition(kVisibleSize / 2);
	return bg;
}

Sprite* Tools::SetBg(const std::string& filename, cocos2d::Node* that)
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
		//子节点随父节点一起淡入淡出
		node->setCascadeOpacityEnabled(true);
		auto delay = DelayTime::create(0.3f);
		auto fadeout = FadeOut::create(1.f);
		auto distory = RemoveSelf::create();
		node->runAction(Sequence::create(delay, fadeout, distory, NULL));
		break;
	}
	case SwitchSceneType::FadeIn:
	{
		//子节点随父节点一起淡入淡出
		node->setCascadeOpacityEnabled(true);
		//要先设置节点透明才可以有效果
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
	case SwitchSceneType::LeftToRight:
	{
		node->setPosition(100, 0);
		auto move = MoveTo::create(0.35f, Vec2(0, 0));
		node->runAction(move);
		break;
	}
	case SwitchSceneType::RightToLeft:
	{
		auto distory = RemoveSelf::create();
		auto move = MoveTo::create(0.2f, Vec2(100, 0));
		auto wait = DelayTime::create(0.2f);
		node->runAction(Sequence::create(wait, move, distory, NULL));
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
	//设置tag供拿出
	sound_menutoggle->setTag(0);
	auto soundmenu = Menu::create(sound_menutoggle, NULL);
	assert(soundmenu != NULL);
	that->addChild(soundmenu);
	soundmenu->setPosition(pos);
	return soundmenu;
}

cocos2d::Label* Tools::LabelCreateTTF(cocos2d::Vec2&& pos,const std::string& words, std::string&& ttf ,float size, Node* that)
{
	auto label = Label::createWithTTF(words, ttf, size);
	assert(label);
	that->addChild(label);
	label->setPosition(pos);
	return label;
}

cocos2d::Label* Tools::LabelCreateSystem(const cocos2d::Vec2& pos, const std::string& words ,std::string&& ttf, float size, Node* that)
{
	auto label = Label::createWithSystemFont(words, ttf, size);
	assert(label);
	that->addChild(label);
	label->setPosition(pos);
	return label;
}

cocos2d::Sprite* Tools::SpriteCreate(const cocos2d::Vec2& pos, std::string&& filename , cocos2d::Node* that)
{
	auto sprite = Sprite::create(filename);
	assert(sprite != NULL);
	sprite->setPosition(pos);
	that->addChild(sprite);
	return sprite;
}

cocos2d::ui::TextField* Tools::TextCreate(const cocos2d::Vec2& pos, std::string&& words, int maxlen, cocos2d::Node* that)
{
	auto text = TextField::create();
	assert(text);
	text->setPosition(pos);
	text->setFontName("微软雅黑");
	text->setFontSize(36);
	text->setPlaceHolder(words);
	that->addChild(text, 2);
	text->setMaxLengthEnabled(true);
	text->setMaxLength(maxlen);
	return text;
}




