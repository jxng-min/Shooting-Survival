#include "AboutScene.h"

Scene* AboutScene::createScene()
{
	auto about_scene = Scene::create();

	auto head_layer = AboutScene::create();
	about_scene->addChild(head_layer);

	return about_scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
		return false;

	return true;
}