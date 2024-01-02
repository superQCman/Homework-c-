#pragma once
#ifndef __GAME_FIRST_H__
#define __GAME_FIRST_H__

#include "cocos2d.h"
#include"Scene_one.h"
#include "ui/CocosGUI.h"
#include<vector>
#include<deque>
#include "player.h"
#include"Barrier.h"
using namespace cocos2d;

class Game_first :public Scene_one
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Game_first);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool isKeyPressed = false;
	void onDelayEnded(float dt);
	Sprite* Boom(cocos2d::Vec2 position);
	
private:
	int barrier_num = 0;
	int pause = 0;
	double groundY=0;
	Sprite* background;
	//Sprite** barriers=new Sprite* [5];
	//Sprite*sprite;
	Base_player* fireboy;
	Sprite* Land,*Land2;
	//Sprite* barrier,*Dangang,*barrier2,*barrier_back;
	std::vector<Barrier_base*> Barrier_list;
	std::vector<Barrier_base*> Barrier_back_list;
	std::vector<Barrier_base*> Barrier_NotMove_list;
	std::vector <std::vector< Barrier_base* >> Barrier_ALL;
	std::deque<weapon*> Weapon;
	std::deque<Rect>weapon_list;
	std::vector<Rect> barrier_list;
	std::vector<Barrier_base*> barrier_list_origin;
	std::vector<Rect> coin_list;
	std::vector<Barrier_base*> Coin_list;
	Label* show_reward=NULL;
	Label* show_blood = NULL;
	Label* show_accuracy = NULL;
	Label* show_warning = NULL;
	ui::Button* return_button;
	float velocity=-50,velocity2=-200,velocity_back=-200,velocity_barrier=-200;
	bool End = false;
	bool succeed = false;
	bool rand_barrier = false,rand_back=false;
};
#endif

