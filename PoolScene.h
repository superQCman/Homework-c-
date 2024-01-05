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
    int n; // 用于跟踪按钮点击
    cocos2d::Sprite* spriteArray[4]; // 存储五张图片的精灵
    void spriteTouched(cocos2d::Ref* pSender, float newYPosition); // 更新后的点击事件处理函数，添加了一个float参数
};