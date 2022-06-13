#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"

/**
* @brief 本地数据
*/
namespace PlistData 
{
//public:

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
	 void addDate(const std::string& id, const std::string&& path);

	/**
	* @brief 读取所需数据
	*/
	 std::string getDataByType(DataType type);

	/**
	* @brief 写入数据
	*/
	 void WriteDataByType(DataType type,const std::string&);

	/**
	* @brief 初始新用户数据
	*/
	 cocos2d::ValueMap& initData(const std::string& id);

	/**
	* @brief 用于重新登录账户
	*/
	 void reset();



//private:

	////存数据的map
	//static cocos2d::ValueMap _map;

	////是否已读数据
	//static bool _exit;

	////路径
	//static std::string _path;

}
