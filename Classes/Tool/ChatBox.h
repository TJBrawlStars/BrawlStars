//2151396 张靖凯

#pragma once

/**
* @class ChatBox
* @brief 聊天室
*/

#include "cocos2d.h"
#include "Const/Const.h"
#include "Tool/Data.h"
#include <vector>
#include <string>

extern std::vector<HeroData> herodataVec;

class ChatBox : public cocos2d::Sprite
{
	//每一次的输入信息
	CC_SYNTHESIZE(std::string, _message, Message);

private:
	std::vector<cocos2d::Label*> _labelMessages;
	cocos2d::Label* _labelInputMessage;
	std::string _defaultHeroName; 
	std::size_t _messageSize;

	static int enterCount;

	//每次的UI Label
	cocos2d::Label* _labelMessage;

public:
	std::vector<std::string> _messages;
	std::vector<std::string>& getVectorOfString() { return _messages; }
	void setVectorOfString(const std::vector<std::string>& messages) { _messages = messages; }

	int getHeroNotRobotNum();

	void addLabelMessages();
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

	void enterToUpdateMessage();

	void backspaceTodateMessage();

	void setDefaultHeroName(std::string heroid);

	void updateChatBox(); 

	void messagesOnScreen(float fdelta);

	virtual bool init() override;

	CREATE_FUNC(ChatBox); 

	ChatBox();

};