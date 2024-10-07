#include "MenuScene.h"

Scene* MenuScene::createScene()
{
    auto menu_scene = Scene::create();

    auto head_layer = MenuScene::create();
    menu_scene->addChild(head_layer);

    return menu_scene;
}

bool MenuScene::init()
{
    if (!Layer::init())
        return false;

    InitData();
    InitBackground();
    InitTitle();

    return true;
}

void MenuScene::InitData()
{
    m_window_size = Director::getInstance()->getWinSize();
}

void MenuScene::InitBackground()
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

void MenuScene::InitTitle()
{
    auto title_layer = Layer::create();
    title_layer->setTag(TAG_LAYER_TITLE);
    this->addChild(title_layer);

    auto title_label = Label::createWithTTF("SHOOTING SURVIVAL", "StarDust.ttf", 35);
    title_label->setPosition(Point(m_window_size.width / 2, m_window_size.height / 2 + 35));
    title_layer->addChild(title_label);

    InitMenu();
}

void MenuScene::InitMenu()
{
    auto title_layer = (Layer*)this->getChildByTag(TAG_LAYER_TITLE);

    auto about_label = Label::createWithTTF("ABOUT", "StarDust.ttf", 15);
    auto start_label = Label::createWithTTF("START", "StarDust.ttf", 15);
    auto quit_label = Label::createWithTTF("QUIT", "StarDust.ttf", 15);

    auto about_item = MenuItemLabel::create(about_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    about_item->setTag(TAG_ITEM_ABOUT);

    auto start_item = MenuItemLabel::create(start_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    start_item->setTag(TAG_ITEM_START);

    auto quit_item = MenuItemLabel::create(quit_label, CC_CALLBACK_1(MenuScene::MenuCallback, this));
    quit_item->setTag(TAG_ITEM_QUIT);

    auto title_menu = Menu::create(about_item, start_item, quit_item, NULL);
    title_menu->setAnchorPoint(Point(0.5, 0.5));
    title_menu->setPosition(Point(m_window_size.width / 2, m_window_size.height / 2 - 50));
    title_menu->alignItemsHorizontallyWithPadding(25);
    title_layer->addChild(title_menu);
}

void MenuScene::MenuCallback(Ref* sender)
{
    auto item = (MenuItemLabel*)sender;

    switch (item->getTag())
    {
    case TAG_ITEM_ABOUT:
        Director::getInstance()->pushScene(AboutScene::createScene());
        break;

    case TAG_ITEM_START:
        Director::getInstance()->replaceScene(GameScene::createScene());
        break;

    case TAG_ITEM_QUIT:
        Director::getInstance()->end();
        break;
    }
}