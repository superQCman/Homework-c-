// PoolScene.h
#include "cocos2d.h"
using namespace cocos2d;
class PoolScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    Label* show_reward=nullptr;
    // implement the "static create()" method manually
    CREATE_FUNC(PoolScene);

private:
    int n; // ���ڸ��ٰ�ť���
    cocos2d::Sprite* spriteArray[4]; // �洢����ͼƬ�ľ���
    void spriteTouched(cocos2d::Ref* pSender, float newYPosition); // ���º�ĵ���¼��������������һ��float����
};