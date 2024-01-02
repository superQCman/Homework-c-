#ifndef __DIFFICULTY__
#define __DIFFICULTY__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;

class Difficulty : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    ui::Button* return_button;
    CREATE_FUNC(Difficulty);
    // 选择难度的方法
    void selectDifficulty(int level);

private:
    cocos2d::Sprite* spriteD;
    cocos2d::Label* coinLabel; // 显示金币数量的标签
    int level = 1;  // 难度级别
    cocos2d::Label* levelLabel;  // 用于显示难度级别的标签
};

#endif 

