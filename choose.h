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
    // ѡ���Ѷȵķ���
    void selectDifficulty(int level);
    void selectDifficulty_2(int level);
    void selectDifficulty_3(int level);

private:
    cocos2d::Sprite* spriteD,*spriteD2,*spriteD3;
    cocos2d::Label* coinLabel; // ��ʾ��������ı�ǩ
    int level = 1;  // �Ѷȼ���
    cocos2d::Label* levelLabel;  // ������ʾ�Ѷȼ���ı�ǩ
};

#endif 

