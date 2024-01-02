#pragma once
#include "cocos2d.h"
#include"Scene_one.h"
#include"Barrier.h"
using namespace cocos2d;
class Base_player {
public:
	Base_player(double,std::string,std::string,std::string,int,int position);
	virtual void BigJump(double) = 0;
	virtual void Jump(double) = 0;
	virtual void Move(double) = 0;
	int& get_accuracy_time();
	int& get_sleep_time();
	int& get_small_sleep_time();
	virtual void set_accuracy_time() = 0;
	virtual void set_sleep_time() = 0;
	virtual void set_small_sleep_time() = 0;
	virtual void set_blood() = 0;
	virtual void throw_weapon(Base_player*,std::string,Barrier_base*)=0;
	double time = 0;
	double sleep = 0;
	double full_energy = 0;
	double energy = 0;
	//double small_sleep = 0;
	double velocity_player = 0;
	//bool smaller = true;
	bool faster = true;
	Sprite* sprite;
	Animate* animate;
	Animation* animation;
	RepeatForever* repeat;
	Vector<SpriteFrame*> frames;
	int reward = 0;
	double blood_now = 0;
	double blood = 0;
	int jump_max = 4;
	bool die = false;
	bool ready = true;
	cocos2d::Sequence* sequence=NULL;
	virtual ~Base_player(){}
private:
	int accuracy_time = 0;
	int sleep_time = 0;
	int small_sleep_time = 0;//缩小时间间隔
};

class Fireboy :public Base_player {
public:
	Fireboy(double groudY, std::string first_pic, std::string second_first, std::string second_second, int pic_num, int position) :Base_player(groudY, first_pic, second_first, second_second, pic_num, position) {
		set_accuracy_time();
		set_sleep_time();
		set_blood();
	}
	void BigJump(double);
	void Jump(double);
	void Move(double);
	void set_accuracy_time();
	void set_sleep_time();
	void set_small_sleep_time();
	void set_blood();
	void throw_weapon(Base_player*,std::string,Barrier_base*);
};

class Teacher : public Fireboy {
public:
	Teacher(double groudY, std::string first_pic, std::string second_first, std::string second_second, int pic_num, int position) :Fireboy(groudY, first_pic, second_first, second_second, pic_num, position) {
		set_blood();
	}
	void set_blood();
	void throw_weapon(Base_player*, std::string, Barrier_base*);
};

//Fireboy2，Fireboy3...继承Fireboy，改变sleep_time，blood，accuracy_time

