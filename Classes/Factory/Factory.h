/** @author  ±ÃÏ“› */

#pragma once

#include <string>
#include <vector>
#include <map>

class ClassInfo
{
	std::string classID;
	void* creator;
};

typedef std::vector<std::string> ClassIDVec;

/**
* @class Factory
* @brief base class of factory. factory is a singleton class to create objects.
*/
class Factory
{
public:
	ClassIDVec getClassIDVec() { return _classID; }

protected:
	Factory() = default;
	virtual ~Factory() {}

	void registerClassID(std::string classID) { _classID.push_back(classID); }

	ClassIDVec _classID;
private:

};