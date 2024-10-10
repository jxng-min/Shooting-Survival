#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

#define TAG_SPRITE_PLAYER			1

#define TAG_LAYER_GUI				2
#define TAG_SPRITE_SETTING			3
#define TAG_SPRITE_SHOOTING			4
#define TAG_SPRITE_RELOADING		5
#define TAG_UI_SCORE				6
#define TAG_UI_HISCORE				7
#define TAG_UI_LIFE					8
#define TAG_LAYER_SETTING			9
#define TAG_ITEM_BACK				10
#define TAG_ITEM_TITLE				11

#define PADDING_SCREEN_X			50
#define PADDING_SCREEN_Y			100

class GameScene : public Layer
{
private:
	Size m_window_size;

	Point m_pos_start_touch;
	Point m_pos_start_player;

	bool m_is_moving;
	bool m_is_reloading;
	bool m_is_setting;

	Vector<Sprite*> m_enemies;

	Vector<Sprite*> m_bullets;
	Vector<Sprite*> m_bullet_ui;
	int m_bullet_count;

	int m_score;
	int m_high_score;
	
	Vector<Sprite*> m_lifes;
	int m_life;

public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

	void InitFrame();
	void InitData();
	void InitTouchListener();

	void InitGUI();
	void InitBackground();
	void InitSettingUI();
	void InitShootingUI();
	void InitReloadingUI();
	void InitScoreUI();
	void InitHighScoreUI();
	void InitLifeUI();
	void InitBulletUI();
	void InitSettingLayer();

	void InitPlayer();
	void PlayerMoveAnimation();
	void ConstraintPlayerPostion();

	void SetEnemy(float delta);
	void ResetEnemy(Ref* sender);

	void SetBullet(float delta);
	void ResetBullet(Ref* sender);

	void CollisionBullet();
	void CollisionPlayer();

	void ReloadBullet();
	void RunEnemyToPlayer(float delta);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);

	virtual void update(float delta);

	void SettingMenuCallback(Ref* sender);
};

#endif