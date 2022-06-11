//2151396 张靖凯

#include "ChatBox.h"
#include "Net/Client.h"

int ChatBox::enterCount = 0;

bool ChatBox::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//初始化
	this->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
	this->initWithFile("ChatBox/ChatBoxBG.png");

	_labelInputMessage = cocos2d::Label::createWithTTF("", "fonts/HELVETICAEXT-NORMAL.ttf", 15);
	_labelInputMessage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT); 
	_labelInputMessage->setPosition(cocos2d::Vec2(20, 14.5f));
	_labelInputMessage->setGlobalZOrder(kFightUI + 1);
	this->addChild(_labelInputMessage);

	updateChatBox();

	return true;
}

void ChatBox::backspaceTodateMessage()
{
	if (_message.size() == 0)
	{
		return;
	}
	_messageSize--;
	_message.pop_back();
	_labelInputMessage->setString(_message);
	return;
}

ChatBox::ChatBox()
{
	_messageSize = 0;
	_defaultHeroName = "";
	_message = "";
}

void ChatBox::updateChatBox()
{
	this->schedule(cocos2d::SEL_SCHEDULE(&ChatBox::messagesOnScreen),0.1f);
}

void ChatBox::messagesOnScreen(float fdelta)
{
	float height = 14.5f;

	int count = static_cast<int>(_messages.size());

	int tempenterCount = enterCount;
	if (count - tempenterCount != 0)
	{
		for (int i = 1; i <= (count - tempenterCount); i++)
		{
			addLabelMessages();
			enterCount++;
		}
	}

	for (auto &i : _messages)
	{
		std::istringstream temp(i);
		std::string datatype;
		temp >> datatype;
		if (datatype == "MSG")
		{
			std::string heroname;
			std::string message;
			temp >> heroname;
			temp >> message;

			i = heroname + ":" + message;
		}
	}

	if (!Client::getInstance() == NULL)
		Client::getInstance()->update(this->_messages);

	for (int i = 0; i < count; i++)
	{
		constexpr float jianGeHeight = 20.0f;
		_labelMessages[i]->setString(_messages[i]);
		_labelMessages[i]->setPosition(20, height + jianGeHeight * (count - i));
		if (_labelMessages[i]->getPosition().y > height + jianGeHeight * 11)
		{
			_labelMessages[i]->setVisible(false);
		}
	}
}

void ChatBox::addLabelMessages()
{
	_labelMessage = cocos2d::Label::createWithTTF("", "fonts/HELVETICAEXT-NORMAL.ttf", 15);
	_labelMessage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	_labelMessage->setGlobalZOrder(kFightUI + 1);
	this->addChild(_labelMessage);

	_labelMessages.push_back(_labelMessage);
}

void ChatBox::updateMessage(char newchar)
{
	if (_messageSize < 15 && newchar != '*')
	{
		_messageSize++;
		_message += newchar;
		_labelInputMessage->setString(_message);
	}
}

void ChatBox::enterToUpdateMessage()
{
	//按enter的次数
	enterCount++;

	//高度
	float height = 14.5f;

	addLabelMessages();
	this->setDefaultHeroName(PlistData::getDataByType(PlistData::DataType::ID));
	_messages.push_back(_defaultHeroName + _message);

	//更新当前message
	_messageSize = 0;
	_message = "";
	_labelInputMessage->setString("");
}

void ChatBox::setDefaultHeroName(std::string heroid)
{
	_defaultHeroName = heroid + ":";
}


char ChatBox::switchKeycodeToChar(cocos2d::EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		return '0';
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		return '1';
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		return '2';
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		return '3';
	case cocos2d::EventKeyboard::KeyCode::KEY_4:
		return '4';
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		return '5';
	case cocos2d::EventKeyboard::KeyCode::KEY_6:
		return '6';
	case cocos2d::EventKeyboard::KeyCode::KEY_7:
		return '7';
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		return '8';
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		return '9';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
		return 'A';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_B:
		return 'B';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_C:
		return 'C';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
		return 'D';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_E:
		return 'E';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_F:
		return 'F';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_G:
		return 'G';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_H:
		return 'H';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_I:
		return 'I';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_J:
		return 'J';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_K:
		return 'K';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_L:
		return 'L';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_M:
		return 'M';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_N:
		return 'N';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_O:
		return 'O';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_P:
		return 'P';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Q:
		return 'Q';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_R:
		return 'R';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
		return 'S';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_T:
		return 'T';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_U:
		return 'U';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_V:
		return 'V';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
		return 'W';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_X:
		return 'X';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Y:
		return 'Y';
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z:
		return 'Z';
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		return 'a';
	case cocos2d::EventKeyboard::KeyCode::KEY_B:
		return 'b';
	case cocos2d::EventKeyboard::KeyCode::KEY_C:
		return 'c';
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		return 'd';
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		return 'e';
	case cocos2d::EventKeyboard::KeyCode::KEY_F:
		return 'f';
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		return 'g';
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		return 'h';
	case cocos2d::EventKeyboard::KeyCode::KEY_I:
		return 'i';
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		return 'j';
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		return 'k';
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		return 'l';
	case cocos2d::EventKeyboard::KeyCode::KEY_M:
		return 'm';
	case cocos2d::EventKeyboard::KeyCode::KEY_N:
		return 'n';
	case cocos2d::EventKeyboard::KeyCode::KEY_O:
		return 'o';
	case cocos2d::EventKeyboard::KeyCode::KEY_P:
		return 'p';
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
		return 'q';
	case cocos2d::EventKeyboard::KeyCode::KEY_R:
		return 'r';
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		return 's';
	case cocos2d::EventKeyboard::KeyCode::KEY_T:
		return 't';
	case cocos2d::EventKeyboard::KeyCode::KEY_U:
		return 'u';
	case cocos2d::EventKeyboard::KeyCode::KEY_V:
		return 'v';
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		return 'w';
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
		return 'x';
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		return 'y';
	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		return 'z';
	default:
		return '*';
		break;
	}
}

int ChatBox::getHeroNotRobotNum()
{
	size_t heronum = herodataVec.size();

	int count = 0;
	//将第一个设置为主角
	for (int i = 0; i < heronum; i++)
	{
		//初始化操作
		std::istringstream temp(herodataVec[i].name_isRobot);
		std::string heroname;
		std::string isRobot;
		temp >> heroname;
		temp >> isRobot;

		if (isRobot == "false")
			count++;
	}

	return count;
}
