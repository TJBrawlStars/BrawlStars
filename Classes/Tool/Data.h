#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 本地数据
*/
class PlistData 
{
public:

	/**
	* @brief 数据类型
	*/
	enum class DataType
	{
		ID,
		Profile,
		Name,
		Cups,
		Money,
		Figure,
		Log,
	};

	/**
	* @brief 添加用户数据By ID
	*/
	static void addDate(const std::string& id, const std::string&& path);

	/**
	* @brief 读取所需数据
	*/
	static std::string getDataByType(DataType type);

	/**
	* @brief 写入数据
	*/
	static void WriteDataByType(DataType type,const std::string&);

	/**
	* @brief 初始新用户数据
	*/
	static cocos2d::ValueMap& initData(const std::string& id);

private:

	//存数据的map
	static cocos2d::ValueMap _map;

	//是否已读数据
	static bool _exit;

	//路径
	static std::string _path;

};
