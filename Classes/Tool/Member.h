#pragma once
#include<string>

/**
* @brief 对战成员数目和管理(机器人的数目和真人的数目）
*/
class Member
{
public:

	/**
	* @brief 如函数名所描述
	* @param 1为添加一个 0为删除一个
	*/
	bool setRobot(bool is_plus);

	bool setHuman(bool is_plus);

	int getHuman() const { return _human; }

	int getRobot() const { return _robot; }

    //必有房主一个human
	Member() :_robot(0), _human(1) {};

private:

	int _robot;

	int _human;

};

class HumanData
{

private:
	//我觉得联机的话需要记录ip 
	std::string _hero_name;

public:

	HumanData(std::string&& name) :_hero_name(name) {};

	std::string GetName() { return _hero_name; }

};
