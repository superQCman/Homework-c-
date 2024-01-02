#pragma once

#ifndef __GAME_FIRST_SECOND_H__
#define __GAME_FIRST_SECOND_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<vector>
#include<deque>
#include "player.h"
#include"Barrier.h"
#include"Game_first.h"
class game_first_second :public Game_first{
	friend double y_velocity(Sprite* fireboy, Sprite* i, int x_velocity);
public:
	// 设置随机数种子
	bool isKeyR = false, isKeyUp = false, isKeyUpUp = false, isKeyL = false, isKeyD = false, isKeyCD = false;
	JumpBy* Uper, * heigh_uper;RepeatForever* move, * move_L;int temp = 0;
	int replace = 0;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool isKeyPressed = false;
	void onDelayEnded(float dt);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void timerCallback(float);
	CREATE_FUNC(game_first_second);
protected:
	int barrier_num = 0;
	int pause = 0;
	double groundY = 0;
	bool BossWeponCheck = true;
	Sprite* background;
	//Sprite** barriers=new Sprite* [5];
	//Sprite*sprite;
	Base_player* fireboy;
	Base_player* boss;
	Sprite* Land, * Land2;
	//Sprite* barrier,*Dangang,*barrier2,*barrier_back;
	std::vector<Barrier_base*> Barrier_list;
	std::vector<Barrier_base*> Barrier_back_list;
	std::vector<Barrier_base*> Barrier_NotMove_list;
	std::deque<Barrier_base*> Boss_weapon;
	std::vector <std::vector< Barrier_base* >> Barrier_ALL;
	std::deque<weapon*> Weapon;
	std::deque<Rect>wepon_list;
	std::vector<Rect> barrier_list;
	std::vector<Rect> BossWeapon;
	std::vector<Barrier_base*> barrier_list_origin;
	std::vector<Rect> coin_list;
	std::vector<Barrier_base*> Coin_list;
	Label* show_reward = NULL;
	Label* show_blood = NULL;
	Label* show_boss_blood = NULL;
	Label* show_accuracy = NULL;
	Label* show_warning = NULL;
	ui::Button* return_button;
	float velocity = -50, velocity2 = -200, velocity_back = -200, velocity_barrier = -200;
	bool End = false;
	bool rand_barrier = false, rand_back = false;
};

#endif


