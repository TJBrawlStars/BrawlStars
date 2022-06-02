#include "FigureLayer.h"
USING_NS_CC;
using namespace ui;
//#define NDEBUG
#include<cassert>
#include"Tool/Tools.h"
#include "MainScene.h"
#include "Tool/Data.h"
#include"RoomLayer.h"

bool FigureLayer::init()
{
	if (!Layer::init())
		return false;

	//设置吞噬点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(FigureLayer::onTouchBegan, this);
	Tools::LayerSwallow(listener, this);

	//背景
	_bg = Tools::SetBg(this);

	//读取现已设定的角色,获得角色数字
	_figure = PlistData::getDataByType(PlistData::DataType::Figure);

	//返回按钮
	_back = Tools::ButtonCreate(Vec2(100, kVisibleSize.height - 100), "ui/back.png", this);
	_back->addTouchEventListener([this](Ref*, Widget::TouchEventType)
		{
			//同时把主场景的和房间场景的设置了
		    MainScene::GetMainScene()->SetFigure(_figure);
			RoomLayer::setSelf(_figure);
			PlistData::WriteDataByType(PlistData::DataType::Figure, _figure);
			//做出划上划下的效果
			Tools::SwitchScene(this, Tools::SwitchSceneType::Up);
		});

	//加载现有人物图像
	SetFigures();

	return true;
}

void FigureLayer::SetFigures()
{
	std::string name;
	for (int i = 1; i <= kNum; ++i)
	{
		//超过三个换行
		name = "ui/figure" + Value(i).asString() + ".jpg";
		auto figure = Tools::ButtonCreateN(Vec2(kVisibleSize.width / 2 - (2 - i) * 250, kVisibleSize.height / 2 + 150 - (i - 1) / 3 * 300)
			, name, this);
		//马上跟上初始化设定打勾的角色
		if (Value(i).asString().at(0) == _figure.at(9))
			_select = Tools::SpriteCreate(figure->getPosition(), "ui/select.png", this);
		figure->addTouchEventListener([this](Ref* ref, Widget::TouchEventType type)
			{
				//这边本来直接在匿名函数里使用了&figure，但是匿名函数在运行的过程中figure已被释放，是要在ref里取出这个按钮
				if (type == Widget::TouchEventType::ENDED)
				{
					auto button = dynamic_cast<Button*>(ref);
					_figure = button->getNormalFile().file;
					auto distory = RemoveSelf::create();
					_select->runAction(distory);
					_select = Tools::SpriteCreate(button->getPosition(), "ui/select.png", this);
				}
			});
	}
}
