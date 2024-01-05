#include "Barrier.h"
#include "cocos2d.h"
#include"Scene_one.h"
#include <cstdlib>
#include "ui/CocosGUI.h"
#include"AppDelegate.h"
#include "store_message.h"
using namespace cocos2d;

//��ʼ������
Barrier_base::Barrier_base(std::string png) {
	auto barrier_ = AutoPolygon::generatePolygon(png);
	sprite = Sprite::create(barrier_);
}

//�����������ϰ���rocket�ƶ��ٶ�
void rocket::set_velocity(int v) {
	velocity = v;
}
//�����������ϰ���rocket_back�ƶ��ٶ�
void rocket_back::set_velocity(int v) {
	velocity = v;
}
//����������Notmove�ƶ��ٶ�
void NotMove::set_velocity(int v) {
	velocity = v;
}

//����������rocket��ˢ��λ��
void rocket::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(2560 + sprite->getContentSize().width / 2+rand_position, groundy));
	pos = Vec2(2560 + sprite->getContentSize().width / 2 + rand_position, groundy);
}

//����������rocket_back��ˢ��λ��
void rocket_back::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(-sprite->getContentSize().width- rand_position, groundy));
	pos = Vec2(2560 + sprite->getContentSize().width / 2 + rand_position, groundy);
}
//����������NotMove��ˢ��λ��
void NotMove::set_position(int rand_position,double groundy) {
	sprite->setPosition(Vec2(2560/2+2560+rand_position, groundy));
}
//��������ϰ���NotMove������
void NotMove::set_rand_num(int randnum) {
	rand_num = randnum;
}
void NotMove::swing() {
	auto swingRight = RotateTo::create(0.5f, -10); // ����ҡ�ڣ���Сx����ĳߴ�
	auto swingLeft = RotateTo::create(0.5f, 10); // ����ҡ�ڣ��ָ�x����ĳߴ�
	auto sequence = Sequence::create(swingRight, swingLeft, nullptr);
	// �������������ó�����ѭ��
	auto swingAction = RepeatForever::create(sequence);

	// �þ���ִ�иö���
	sprite->runAction(swingAction);
}
void rocket_back::set_rand_num(int randnum) {
	rand_num = randnum;
}
void rocket::set_rand_num(int randnum) {
	rand_num = randnum;
}
//�����ܴݻٵ��ϰ���
void razor::SetDistroyNum() {
	if(store_message::chooseWeapon[0]==1)distroy_num = store_message::WeaponPower[0];
	else distroy_num = store_message::WeaponPower[1];
}
void pensil::SetDistroyNum() {
	if (store_message::chooseWeapon[2] == 1)distroy_num = store_message::WeaponPower[2];
	else distroy_num = store_message::WeaponPower[3];
}