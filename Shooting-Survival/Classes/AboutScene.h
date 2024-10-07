#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class AboutScene : public Layer
{
private:
	Size m_window_size;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(AboutScene);
};

#endif