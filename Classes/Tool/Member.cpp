#include"Tool/Member.h"

bool Member::setRobot(bool is_plus)
{
	if (is_plus)
	{
		if (_robot + 1 <= 10 - _human)
		{
			++_robot;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (_robot - 1 >= 0)
		{
			--_robot;
			return true;
		}
		else
			return false;
	}
}

bool Member::setHuman(bool is_plus)
{
	if (is_plus)
	{
		if (_human + 1 <= 10 - _robot)
		{
			++_human;
			return true;
		}
		else
			return false;
	}
	else
	{
		if (_human - 1 >= 1)
		{
			--_human;
			return true;
		}
		else
			return false;
	}
}