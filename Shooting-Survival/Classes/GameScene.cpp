#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto game_scene = Scene::create();

	auto head_layer = GameScene::create();
	game_scene->addChild(head_layer);

	return game_scene;
}

bool init()
{
	if (!Layer::init())
		return false;

	return true;
}