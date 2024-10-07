#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "AboutScene.h"
#include "GameScene.h"

USING_NS_CC;

#define TAG_LAYER_TITLE             1

#define TAG_ITEM_ABOUT              2
#define TAG_ITEM_START              3
#define TAG_ITEM_QUIT               4

class MenuScene : public Layer
{
private:
    Size m_window_size;

public:
    static Scene* createScene();

    virtual bool init();
    CREATE_FUNC(MenuScene);

    void InitData();
    void InitBackground();
    void InitTitle();
    void InitMenu();

    void MenuCallback(Ref* sender);
};

#endif
