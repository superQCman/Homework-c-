#include "Barrier.h"
#include "cocos2d.h"
#include"Scene_one.h"
#include <cstdlib>
#include "ui/CocosGUI.h"
#include"AppDelegate.h"
#include "store_message.h"
using namespace cocos2d;

//初始化基类
Barrier_base::Barrier_base(std::string png) {
	auto barrier_ = AutoPolygon::generatePolygon(png);
	sprite = Sprite::create(barrier_);
}

//设置派生类障碍物rocket移动速度
void rocket::set_velocity(int v) {
	velocity = v;
}
//设置派生类障碍物rocket_back移动速度
void rocket_back::set_velocity(int v) {
	velocity = v;
}
//设置派生类Notmove移动速度
void NotMove::set_velocity(int v) {
	velocity = v;
}

//设置派生类rocket的刷新位置
void rocket::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(2560 + sprite->getContentSize().width / 2+rand_position, groundy));
	pos = Vec2(2560 + sprite->getContentSize().width / 2 + rand_position, groundy);
}

//设置派生类rocket_back的刷新位置
void rocket_back::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(-sprite->getContentSize().width- rand_position, groundy));
	pos = Vec2(2560 + sprite->getContentSize().width / 2 + rand_position, groundy);
}
//设置派生类NotMove的刷新位置
void NotMove::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(2560/2+2560+rand_position, groundy));
}
//设置随机障碍物NotMove的数量
void NotMove::set_rand_num(int randnum) {
	rand_num = randnum;
}
void NotMove::swing() {
	auto swingRight = RotateTo::create(0.5f, -10); // 向右摇摆，缩小x方向的尺寸
	auto swingLeft = RotateTo::create(0.5f, 10); // 向左摇摆，恢复x方向的尺寸
	auto sequence = Sequence::create(swingRight, swingLeft, nullptr);
	// 将动作序列设置成无限循环
	auto swingAction = RepeatForever::create(sequence);

	// 让精灵执行该动作
	sprite->runAction(swingAction);
}
void rocket_back::set_rand_num(int randnum) {
	rand_num = randnum;
}
void rocket::set_rand_num(int randnum) {
	rand_num = randnum;
}
//设置能摧毁的障碍物
void razor::SetDistroyNum() {
	if(store_message::chooseWeapon[0]==1)distroy_num = store_message::WeaponPower[0];
	else distroy_num = store_message::WeaponPower[1];
}
void pensil::SetDistroyNum() {
	if (store_message::chooseWeapon[2] == 1)distroy_num = store_message::WeaponPower[2];
	else distroy_num = store_message::WeaponPower[3];
}