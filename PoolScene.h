// PoolScene.h
#include "cocos2d.h"
#include"Scene_one.h"
using namespace cocos2d;
class PoolScene : public Scene_one {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    Label* show_reward=nullptr;
    // implement the "static create()" method manually
    CREATE_FUNC(PoolScene);

private:
    Label* show_warning = NULL;
    int n; // ���ڸ��ٰ�ť���
    cocos2d::Sprite* spriteArray[4]; // �洢����ͼƬ�ľ���
    void spriteTouched(cocos2d::Ref* pSender, float newYPosition); // ���º�ĵ���¼��������������һ��float����
};