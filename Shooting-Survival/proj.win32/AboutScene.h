#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_LAYER_UI				1

#define TAG_ITEM_BACK				2

class AboutScene : public Layer
{
private:
	Size m_window_size;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(AboutScene);

	void InitData();
	void InitBackground();
	void InitUI();
	void InitMenu();

	void MenuCallback(Ref* sender);
};

#endif