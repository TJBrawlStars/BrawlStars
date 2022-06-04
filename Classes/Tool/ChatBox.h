//2151396 张靖凯

#pragma once

/**
* @class ChatBox
* @brief 聊天室
*/

#include "cocos2d.h"
#include "Const/Const.h"
#include <vector>
#include <string>

class ChatBox : public cocos2d::Sprite
{
	//每一次的输入信息
	CC_SYNTHESIZE(std::string, _message, Message);

private:

	//联机时每个人储存的信息
	//std::vector<std::string> _messages;
	//cocos2d::Label* _labelMessages[10];

	cocos2d::Label* _labelInputMessage;
	std::string _defaultHeroName; 
	std::size_t _messageSize;

public:
	/**
	* @fn switchKeycodeToChar
	* @brief 每一个字符转换成char
	*/
	static char switchKeycodeToChar(cocos2d::EventKeyboard::KeyCode keyCode);

	/**
	* @fn updateMessage
	* @brief 更新输入的每一个字符
	*  输入长度小于15 | 输入'*'      ///>等于没输入
	*/
	void updateMessage(char newchar);

	void setDefaultHeroName(std::string heroid);

	virtual bool init() override;

	CREATE_FUNC(ChatBox); 

	ChatBox();
};