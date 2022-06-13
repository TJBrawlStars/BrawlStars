#include "Data.h"
USING_NS_CC;
using namespace ui;
#define NDEBUG
#include<cassert>
#include"Factory/HeroFactory.h"
#pragma execution_character_set("utf-8") 

namespace PlistData
{

	bool _exit = false;
	 ValueMap _map;
	 std::string _path = "";

	void PlistData::addDate(const std::string& id, const std::string&& path)
	{
		//这个文件废了我一下午
		if (FileUtils::getInstance()->isFileExist(path))
			_map = FileUtils::getInstance()->getValueMapFromFile(path);
		else
		{
			if (!FileUtils::getInstance()->writeValueMapToFile(initData(id), path))
				assert(0);
		}
		_exit = true;
		_path = path;
	}

	std::string PlistData::getDataByType(DataType type)
	{
		assert(_exit == true);
		switch (type)
		{
		case(DataType::ID):
			return _map["ID"].asString();
			break;
		case(DataType::Name):
			return _map["Name"].asString();
			break;
		case(DataType::Profile):
			return _map["Profile"].asString();
			break;
		case(DataType::Figure):
			return _map["Figure"].asString();
			break;
		case(DataType::Cups):
			return _map["Cups"].asString();
			break;
		case(DataType::Money):
			return _map["Money"].asString();
			break;
		default:
			return "";
		}
	}

	void PlistData::WriteDataByType(DataType type, const std::string& data)
	{
		assert(_exit == true);
		switch (type)
		{
		case(DataType::ID):
			_map["ID"] = data;
			break;
		case(DataType::Name):
			_map["Name"] = data;
			break;
		case(DataType::Profile):
			_map["Profile"] = data;
			break;
		case(DataType::Figure):
			_map["Figure"] = data;
			break;
		case(DataType::Cups):
			_map["Cups"] = data;
			break;
		case(DataType::Money):
			_map["Money"] = data;
			break;
		default:
			break;
		}
		FileUtils::getInstance()->writeToFile(_map, _path);
	}

	ValueMap& PlistData::initData(const std::string& id)
	{
		auto name = HeroFactory::getInstance()->createWithClassID("Beiya")->getHeroPicture();
		_map.insert(std::make_pair("ID", id));
		_map.insert(std::make_pair("Name", "空弦小姐的猫猫"));
		_map.insert(std::make_pair("Profile", "ui/info1.png"));
		_map.insert(std::make_pair("Cups", "0"));
		_map.insert(std::make_pair("Money", "0"));
		_map.insert(std::make_pair("Figure", name));
		return _map;
	}

	void PlistData::reset()
	{
		_exit = false;
	}
}
