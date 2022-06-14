//2151396 张靖凯

#include "View/GameScene.h"
#include "Const/Const.h"

using namespace std;
USING_NS_CC;

extern std::vector<HeroData> herodataVec;

/********************************** 计时器 *****************************************/

/**
* @brief 初始化计时器
*/
//void GameScene::addTimer()
//{
//	_timer = MyTimer::create();
//	this->addChild(_timer, kTimerPriority);
//
//}
//
//void GameScene::updateMyTimerPosition()
//{
//	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
//
//	cocos2d::Label* tmptimerInfo = _timer->getMyTimerInfo();
//	cocos2d::Sprite* tmptimerInfoBG = _timer->getMyTimerInfoBG();
//
//	tmptimerInfoBG->setPosition(this->destPos(this->getHero()->getPosition()) + cocos2d::Vec2(-visibleSize.width / 2, visibleSize.height / 2));
//	tmptimerInfo->setPosition(this->destPos(this->getHero()->getPosition()) + cocos2d::Vec2(55 - visibleSize.width / 2, visibleSize.height / 2));
//	tmptimerInfo->setString((_timer->getHour() + ":" + _timer->getMinute() + ":" + _timer->getSecond()));
//}


/********************************** 聊天室 *****************************************/

/**
* @brief 初始化聊天室
*/
void GameScene::addChatBox()
{
	//聊天室按钮
	_chatboxSwitch = Sprite::create("ChatBox/ChatBox.png");
	_chatboxSwitch->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(_chatboxSwitch);
	_chatboxSwitch->setGlobalZOrder(kFightUI);

	//聊天框
	_chatBox = ChatBox::create();
	_chatBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	this->addChild(_chatBox);
	_chatBox->setGlobalZOrder(kFightUI);
	_chatBox->setVisible(false);
}

void GameScene::updateChatBoxPosition()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	//聊天按钮
	_chatboxSwitch->setPosition(this->destPos(this->getHero()->getPosition()) + cocos2d::Vec2(visibleSize.width / 2, -visibleSize.height / 2));

	//聊天框
	_chatBox->setPosition(this->destPos(this->getHero()->getPosition()) + cocos2d::Vec2(visibleSize.width / 2, -visibleSize.height / 2 + _chatboxSwitch->getContentSize().height));
}


/******************************* 控制器 ************************************/


bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	Rect worldchatboxSwitch = Rect(_chatboxSwitch->getPosition().x-46, _chatboxSwitch->getPosition().y, 46, 41);
	auto touchlocation = _player->convertToNodeSpace(touch->getLocation());

	//点中框了
	if (worldchatboxSwitch.containsPoint(touchlocation))
	{
		if (_isChatboxOpen)
		{
			_isChatboxOpen = false;
			_chatBox->setVisible(false);
			return false;
		}
		_isChatboxOpen = true;
		_chatBox->setVisible(true);
		return false;
	}

	return true;
}

bool GameScene::onPressKey(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (_isChatboxOpen)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		{
			_chatBox->enterToUpdateMessage(); 
		} 
		else if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		{
			_chatBox->backspaceTodateMessage();
		}
		else
		{
			_chatBox->updateMessage(ChatBox::switchKeycodeToChar(keyCode));
		}
	}

	return true;
}

bool GameScene::onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event)
{

	return false;
}

void GameScene::initTouchAndKeyListener()
{
	//创建触摸监听器
	_gmlistenerTouch = EventListenerTouchOneByOne::create();
	//绑定监听事件
	_gmlistenerTouch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_gmlistenerTouch, this);

	//创建键盘监听器
	_gmlistenerKeyBoard = EventListenerKeyboard::create();
	//绑定监听事件
	_gmlistenerKeyBoard->onKeyPressed = CC_CALLBACK_2(GameScene::onPressKey, this);
	_gmlistenerKeyBoard->onKeyReleased = CC_CALLBACK_2(GameScene::onReleaseKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_gmlistenerKeyBoard, this);

}


