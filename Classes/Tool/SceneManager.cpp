#include "SceneManager.h"

SceneManager* SceneManager::_scene_manager = NULL;

SceneManager* SceneManager::getInstance()
{
	if (_scene_manager == NULL)
	{
		_scene_manager = new SceneManager();
		//容错处理
		if (_scene_manager)
		{
			_scene_manager->autorelease();
			_scene_manager->retain();
		}
		else
		{
			CC_SAFE_DELETE(_scene_manager);
			_scene_manager = NULL;
		}
	}
	return _scene_manager;
}

void SceneManager::changeScene(EnumSceneType type, int operate)
{
	//断言检查输入
	assert(type <= EnumSceneType::en_Max && type >= EnumSceneType::en_Min);

	Director* director = Director::getInstance();
	if (operate != 2)
	{
		Scene* scene = NULL;
		switch (type)
		{
		case EnumSceneType::en_MainScene:
			scene = MainScene::create();
			break;
		case EnumSceneType::en_GameScene:
			scene = GameScene::create();
			break;
		case EnumSceneType::en_SettlementScene:
			scene = SettlementScene::create();
			break;
		case EnumSceneType::en_PauseScene:
			scene = PauseScene::create();
			break;
		}

		assert(scene != NULL);

		if (operate == 0)
		{
			const Scene* cur_scene = director->getRunningScene();
			if (cur_scene == NULL)
			{
				director->runWithScene(scene);
				_first = false;
			}
			else
				director->replaceScene(TransitionCrossFade::create(0.5f, scene));
		}
		else if (operate == 1)
			director->pushScene(TransitionCrossFade::create(0.5f, scene));
	}
	else
		director->popScene();
}
