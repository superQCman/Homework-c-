#pragma once
#ifndef __SCENE_ONE_H__
#define __SCENE_ONE_H__

#include "cocos2d.h"
using namespace cocos2d;

class sprite :public Sprite {
public:
    virtual void movement() = 0;
};
class Scene_one : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void update(float delta);
    void setCloseItem();
    MenuItemImage* closeItem;
    CREATE_FUNC(Scene_one);//CREATE_FUNC �궨����һ����̬�Ĺ����������÷�������ʵ����һ���������󣬲��Զ����ó�������� init �������г�ʼ����
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Label* show_reward = NULL;
private:
    Sprite* background;
    Sprite* background2;
    float velocity;
};
#endif


