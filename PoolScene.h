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
    int n; // 用于跟踪按钮点击
    cocos2d::Sprite* spriteArray[4]; // 存储五张图片的精灵
    void spriteTouched(cocos2d::Ref* pSender, float newYPosition); // 更新后的点击事件处理函数，添加了一个float参数
};