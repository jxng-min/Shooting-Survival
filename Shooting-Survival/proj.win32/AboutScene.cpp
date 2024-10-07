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

    InitData();
    InitBackground();
    InitUI();

	return true;
}

void AboutScene::InitData()
{
    m_window_size = Director::getInstance()->getWinSize();
}

void AboutScene::InitBackground()
{
    auto background_layer = Layer::create();
    this->addChild(background_layer);

    auto background_sprite1 = Sprite::create("road.jpg");
    background_sprite1->setAnchorPoint(Point::ZERO);
    background_sprite1->setPosition(Point(0, 60));
    background_layer->addChild(background_sprite1);

    auto background_sprite2 = Sprite::create("road.jpg");
    background_sprite2->setAnchorPoint(Point::ZERO);
    background_sprite2->setPosition(Point(600, 60));
    background_layer->addChild(background_sprite2);

    auto background_sprite3 = Sprite::create("road.jpg");
    background_sprite3->setAnchorPoint(Point::ZERO);
    background_sprite3->setPosition(Point(1200, 60));
    background_layer->addChild(background_sprite3);

    auto move_action = MoveBy::create(7.0, Point(-1200, 0));
    auto place_action = Place::create(Point::ZERO);
    auto sequence_action = Sequence::create(move_action, place_action, NULL);
    auto repeat_action = RepeatForever::create(sequence_action);
    background_layer->runAction(repeat_action);
}

void AboutScene::InitUI()
{
    auto ui_layer = Layer::create();
    ui_layer->setTag(TAG_LAYER_UI);
    this->addChild(ui_layer);

    auto title_label = Label::createWithTTF("ABOUT", "StarDust.ttf", 35);
    title_label->setPosition(Point(m_window_size.width / 2, m_window_size.height / 2 + 75));
    ui_layer->addChild(title_label);

    auto script_label = Label::createWithTTF("This game is for Cocos2d-x portfolio.", "StarDust.ttf", 15);
    script_label->setPosition(Point(150, m_window_size.height / 2 + 15));
    ui_layer->addChild(script_label);

    auto github_label = Label::createWithTTF("Github: jxng-min", "StarDust.ttf", 10);
    github_label->setPosition(Point(m_window_size.width - 50, 80));
    ui_layer->addChild(github_label);

    InitMenu();
}

void AboutScene::InitMenu()
{
    auto ui_layer = this->getChildByTag(TAG_LAYER_UI);

    auto back_label = Label::createWithTTF("BACK", "StarDust.ttf", 15);

    auto back_item = MenuItemLabel::create(back_label, CC_CALLBACK_1(AboutScene::MenuCallback, this));
    back_item->setTag(TAG_ITEM_BACK);

    auto back_menu = Menu::create(back_item, NULL);
    back_menu->setAnchorPoint(Point::ZERO);
    back_menu->setPosition(Point(m_window_size.width - 30, m_window_size.height - 80));
    back_menu->alignItemsVertically();
    ui_layer->addChild(back_menu);
}

void AboutScene::MenuCallback(Ref* sender)
{
    auto item = (MenuItemLabel*)sender;

    switch (item->getTag())
    {
    case TAG_ITEM_BACK:
        Director::getInstance()->popScene();
        break;
    }
}