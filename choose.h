#ifndef __CHOOSE__
#define __CHOOSE__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"Difficulty.h"
using namespace cocos2d;

class Choose : public Difficulty
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    ui::Button* return_button;
    CREATE_FUNC(Choose);
    // 选择难度的方法
    void selectDifficulty(int level);
    void selectDifficulty_2(int level);
    void selectDifficulty_3(int level);

private:
    cocos2d::Sprite* spriteD,*spriteD2,*spriteD3;
    cocos2d::Label* coinLabel; // 显示金币数量的标签
    int level = 1;  // 难度级别
    cocos2d::Label* levelLabel;  // 用于显示难度级别的标签
};

#endif 

