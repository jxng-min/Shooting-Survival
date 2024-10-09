#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto game_scene = Scene::create();

	auto head_layer = GameScene::create();
	game_scene->addChild(head_layer);

	return game_scene;
}

bool GameScene::init()
{
	if (!Layer::init())
		return false;

    InitFrame();
    InitData();

    InitGUI();

    InitPlayer();
    
    InitTouchListener();

    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SetEnemy), 3.0 + rand() % (3 + 1));

	return true;
}




void GameScene::InitFrame()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Character/Run/Player_Run.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/Run/Enemy_Run.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Shoot/Bullet.plist");
}

void GameScene::InitData()
{
    m_window_size = Director::getInstance()->getWinSize();
    
    m_is_moving = false;
    m_is_reloading = false;

    m_bullet_count = 10;
    m_score = 0;
    m_life = 3;

    m_enemies.clear();
    m_bullets.clear();

    srand(time(NULL));
}

void GameScene::InitTouchListener()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}



void GameScene::InitGUI()
{
    auto gui_layer = Layer::create();
    gui_layer->setTag(TAG_LAYER_GUI);
    this->addChild(gui_layer, 2);

    InitBackground();
    InitSettingUI();
    InitShootingUI();
    InitReloadingUI();
    InitScoreUI();
    InitHighScoreUI();
    InitLifeUI();
    InitBulletUI();
}

void GameScene::InitBackground()
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

void GameScene::InitSettingUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    auto setting_sprite = Sprite::create("Button/SettingButton.png");
    setting_sprite->setScale(0.1);
    setting_sprite->setPosition(Point(m_window_size.width - 15, m_window_size.height - 80));
    setting_sprite->setTag(TAG_SPRITE_SETTING);
    gui_layer->addChild(setting_sprite);
}

void GameScene::InitShootingUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    auto shooting_sprite = Sprite::create("Button/ShootingButton.png");
    shooting_sprite->setScale(0.5);
    shooting_sprite->setPosition(Point(m_window_size.width - 40, 90));
    shooting_sprite->setTag(TAG_SPRITE_SHOOTING);
    gui_layer->addChild(shooting_sprite);
}

void GameScene::InitReloadingUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    auto reloading_sprite = Sprite::create("Button/ReloadingButton.png");
    reloading_sprite->setScale(0.15);
    reloading_sprite->setPosition(Point(m_window_size.width - 95, 90));
    reloading_sprite->setTag(TAG_SPRITE_RELOADING);
    gui_layer->addChild(reloading_sprite);
}

void GameScene::InitScoreUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    auto score_label = Label::createWithTTF(StringUtils::format("SCORE: %04d", m_score), "StarDust.ttf", 10);
    score_label->setColor(Color3B::BLACK);
    score_label->setPosition(Point(m_window_size.width - 40, m_window_size.height - 110));
    score_label->setTag(TAG_UI_SCORE);
    gui_layer->addChild(score_label);
}

void GameScene::InitHighScoreUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    auto hiscore_label = Label::createWithTTF(StringUtils::format("HI       : %04d", 0), "StarDust.ttf", 10);
    hiscore_label->setColor(Color3B::BLACK);
    hiscore_label->setPosition(Point(m_window_size.width - 40, m_window_size.height - 120));
    hiscore_label->setTag(TAG_UI_HISCORE);
    gui_layer->addChild(hiscore_label);
}

void GameScene::InitLifeUI()
{
    auto gui_layer = (Layer*)this->getChildByTag(TAG_LAYER_GUI);

    for (auto i = 0; i < 3; i++)
    {
        auto life_sprite = Sprite::create("Life1.png");
        life_sprite->setScale(0.3);
        life_sprite->setPosition(Point(m_window_size.width - 60 + (i * 20), m_window_size.height - 140));
        gui_layer->addChild(life_sprite);
        m_lifes.pushBack(life_sprite);
    }
}

void GameScene::InitBulletUI()
{

}



void GameScene::InitPlayer()
{
    auto player_sprite = Sprite::createWithSpriteFrameName("Run_1.png");
    player_sprite->setFlippedX(true);
    player_sprite->setScale(3.0);
    player_sprite->setPosition(Point(m_window_size.width / 2, m_window_size.height / 2));
    player_sprite->setTag(TAG_SPRITE_PLAYER);
    this->addChild(player_sprite, 1);

    PlayerMoveAnimation();
}

void GameScene::PlayerMoveAnimation()
{
    auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);

    auto run_animation = Animation::create();
    run_animation->setDelayPerUnit(0.1);

    for (int i = 0; i < 6; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Run_%d.png", i + 1));
        run_animation->addSpriteFrame(frame);
    }

    auto animate = Animate::create(run_animation);
    auto repeat_idle_action = RepeatForever::create(animate);

    player_sprite->runAction(repeat_idle_action);
}

void GameScene::ConstraintPlayerPostion()
{
    auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
    auto player_pos = player_sprite->getPosition();

    if (player_pos.x > m_window_size.width - 30)
        player_pos.x = m_window_size.width - 30;
    
    if (player_pos.x < m_window_size.width / 2 - 40)
        player_pos.x = m_window_size.width / 2 - 40;

    if (player_pos.y > m_window_size.height - 100)
        player_pos.y = m_window_size.height - 100;

    if (player_pos.y < 100)
        player_pos.y = 100;

    player_sprite->setPosition(player_pos);
}




void GameScene::SetEnemy(float delta)
{
    auto x = PADDING_SCREEN_X + rand() % (20 + 1);
    auto y = PADDING_SCREEN_Y + rand() % ((int)m_window_size.height - PADDING_SCREEN_Y * 2);

    auto enemy_sprite = Sprite::createWithSpriteFrameName("slime_run_0.png");
    enemy_sprite->setFlippedX(true);
    enemy_sprite->setScale(3.0);
    enemy_sprite->setPosition(Point(x - 150, y));
    this->addChild(enemy_sprite);

    m_enemies.pushBack(enemy_sprite);

    auto run_animation = Animation::create();
    run_animation->setDelayPerUnit(0.1);

    for (auto i = 0; i < 4; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("slime_run_%d.png", i));
        run_animation->addSpriteFrame(frame);
    }

    auto run_animate_action = Animate::create(run_animation);
    auto enemy_spawn_action = Spawn::create(
                                            MoveTo::create(1.0, Point(x, y)),
                                            RepeatForever::create(run_animate_action),
                                            NULL);

    enemy_sprite->runAction(enemy_spawn_action);
}

void GameScene::ResetEnemy(Ref* sender)
{
    auto enemy_sprite = (Sprite*)sender;

    m_enemies.eraseObject(enemy_sprite);

    this->removeChild(enemy_sprite);
}




void GameScene::SetBullet(float delta)
{
    auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);

    auto bullet_sprite = Sprite::createWithSpriteFrameName("Bullet_0.png");
    bullet_sprite->setScale(3.0);
    bullet_sprite->setFlippedX(true);
    bullet_sprite->setPosition(player_sprite->getPosition() + Point(-25, 5));
    this->addChild(bullet_sprite);

    m_bullets.pushBack(bullet_sprite);

    auto animation = Animation::create();
    animation->setDelayPerUnit(0.1);

    for (auto i = 0; i < 4; i++)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("Bullet_%d.png", i));
        animation->addSpriteFrame(frame);
    }

    auto animate = Animate::create(animation);

    auto spawn_action = Spawn::create(
                                        MoveBy::create(1.0, Point(-m_window_size.width, 0)),
                                        Animate::create(animation),
                                        NULL);

    auto sequence_action = Sequence::create(
                                            spawn_action,
                                            CallFuncN::create(CC_CALLBACK_1(GameScene::ResetBullet, this)),
                                            NULL);

    bullet_sprite->runAction(sequence_action);

    SimpleAudioEngine::getInstance()->playEffect("");   // 총을 쏘는 소리
}

void GameScene::ResetBullet(Ref* sender)
{
    auto bullet_sprite = (Sprite*)sender;

    m_bullets.eraseObject(bullet_sprite);

    this->removeChild(bullet_sprite);
}





void GameScene::CollisionBullet()
{
    auto remove_bullet = Sprite::create();
    auto remove_enemy = Sprite::create();

    for (auto bullet_sprite : m_bullets)
    {
        auto bullet_rect = bullet_sprite->getBoundingBox();

        for (auto enemy_sprite : m_enemies)
        {
            auto enemy_rect = enemy_sprite->getBoundingBox();

            if (bullet_rect.intersectsRect(enemy_rect))
            {
                remove_bullet = bullet_sprite;
                remove_enemy = enemy_sprite;
            }
        }
    }

    if (m_bullets.contains(remove_bullet))
    {
        auto enemy_pos = remove_enemy->getPosition();

        auto enemy_explosion = ParticleExplosion::create();
        enemy_explosion->setPosition(enemy_pos);
        enemy_explosion->setScale(0.1);
        this->addChild(enemy_explosion);

        auto particle_action = Sequence::create(
                                                DelayTime::create(1.0),
                                                RemoveSelf::create(),
                                                NULL);
        enemy_explosion->runAction(particle_action);

        ResetBullet(remove_bullet);
        ResetEnemy(remove_enemy);

        m_score += 150;
        auto gui_score = (Label*)this->getChildByTag(TAG_LAYER_GUI)->getChildByTag(TAG_UI_SCORE);
        gui_score->setString(StringUtils::format("SCORE: %04d", m_score));

        SimpleAudioEngine::getInstance()->playEffect("");   // 슬라임이 죽는 소리
    }
}

void GameScene::CollisionPlayer()
{
    auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
    auto player_rect = player_sprite->getBoundingBox();

    auto remove_enemy = Sprite::create();

    for (auto enemy_sprite : m_enemies)
    {
        auto enemy_rect = enemy_sprite->getBoundingBox();

        if (player_rect.intersectsRect(enemy_rect))
            remove_enemy = enemy_sprite;
    }

    if (m_enemies.contains(remove_enemy))
    {
        auto enemy_pos = remove_enemy->getPosition();

        auto enemy_explosion = ParticleExplosion::create();
        enemy_explosion->setPosition(enemy_pos);
        enemy_explosion->setScale(0.1);
        this->addChild(enemy_explosion);

        auto particle_action = Sequence::create(
            DelayTime::create(1.0),
            RemoveSelf::create(),
            NULL);
        enemy_explosion->runAction(particle_action);

        ResetEnemy(remove_enemy);

        m_lifes.at(3 - m_life)->setVisible(false);
        m_life--;

        SimpleAudioEngine::getInstance()->playEffect("");   // 슬라임이 죽는 소리
        SimpleAudioEngine::getInstance()->playEffect("");   // 플레이어가 데미지를 입는 소리
    }
}



void GameScene::ReloadBullet()
{
    m_bullet_count = 10;
    m_is_reloading = false;
}



void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    for (auto touch : touches)
    {
        auto setting_button = (Sprite*)this->getChildByTag(TAG_LAYER_GUI)->getChildByTag(TAG_SPRITE_SETTING);
        auto setting_rect = setting_button->getBoundingBox();

        auto shooting_button = (Sprite*)this->getChildByTag(TAG_LAYER_GUI)->getChildByTag(TAG_SPRITE_SHOOTING);
        auto shooting_rect = shooting_button->getBoundingBox();

        auto reloading_button = (Sprite*)this->getChildByTag(TAG_LAYER_GUI)->getChildByTag(TAG_SPRITE_RELOADING);
        auto reloading_rect = reloading_button->getBoundingBox();

        auto location = touch->getLocation();
        if (setting_rect.containsPoint(location))
        {

        }
        else if (shooting_rect.containsPoint(location))
        {
            if (m_bullet_count > 0 && !m_is_reloading)
                this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::SetBullet), 0);
            else if (m_bullet_count > 0 && m_is_reloading)
                SimpleAudioEngine::getInstance()->playEffect("");   // 철컥하는 소리
            else
                SimpleAudioEngine::getInstance()->playEffect("");   // 장전하는 소리
        }
        else if (reloading_rect.containsPoint(location))
        {
            if (m_is_reloading)
                return;

            m_is_reloading = true;

            auto sequence_action = Sequence::create(
                                                    DelayTime::create(3.0),
                                                    CallFunc::create(CC_CALLBACK_0(GameScene::ReloadBullet, this)),
                                                    NULL);
            this->runAction(sequence_action);
        }
        else
        {
            if (m_is_moving)
                break;

            m_pos_start_touch = touch->getLocation();

            auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
            m_pos_start_player = player_sprite->getPosition();

            m_is_moving = true;
        }
    }
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
    for (auto touch : touches)
    {
        auto location = touch->getLocation();

        auto pos_change = location - m_pos_start_touch;

        auto player_sprite = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER);
        player_sprite->setPosition(m_pos_start_player + pos_change);
    }
}

void GameScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
    m_is_moving = false;
}




void GameScene::update(float delta)
{
    ConstraintPlayerPostion();
    CollisionBullet();
    CollisionPlayer();
}