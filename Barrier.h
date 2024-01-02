#pragma once
#include "cocos2d.h"
#include"Scene_one.h"
#include "ui/CocosGUI.h"
#include<string>
using namespace cocos2d;
class Barrier_base{
public:
	Barrier_base(std::string png);
	int velocity=0;
	bool rand_barrier=false;
	int rand_num = 0;
	bool interaction = false;
	Sprite* sprite;
	virtual void set_velocity(int) = 0;
	virtual void set_position(int rand_position,double) = 0;
	virtual void set_rand_num(int) = 0;
	Sprite* Boom(cocos2d::Vec2 position);
	virtual void swing() {};
	int WeponSize = 0;
	Vec2 pos;
	virtual ~Barrier_base(){}
};

class rocket :public Barrier_base {
public:
	rocket(std::string png) :Barrier_base(png) {};
	void set_velocity(int v = -200);
	void set_position(int rand_position,double);
	void set_rand_num(int randnum);
};
class rocket_back :public Barrier_base {
public:
	rocket_back(std::string png) :Barrier_base(png) {}
	void set_velocity(int v =100);
	void set_position(int rand_position,double);
	void set_rand_num(int randnum);
};
class weapon :public rocket_back {
public:
	weapon(std::string pic) :rocket_back(pic) {};
	int distroy_num = 0;
	virtual void SetDistroyNum()=0;
};

class pensil : public weapon {
public:
	pensil(std::string pic) :weapon(pic) { SetDistroyNum(); };
	void SetDistroyNum();
};
class razor : public weapon {
public:
	razor(std::string pic) :weapon(pic) { SetDistroyNum(); };
	void SetDistroyNum();
};
class NotMove :public Barrier_base {
public:
	NotMove(std::string png) :Barrier_base(png) {}
	void set_velocity(int v = -200);
	void set_position(int rand_position,double);
	void set_rand_num(int randnum);
	void swing();
};


class Falldown :public Barrier_base {
public:
	Falldown(std::string png) :Barrier_base(png) {}
	void set_velocity();
	void set_position(int rand_position);
	void set_rand_num(int randnum);
};


