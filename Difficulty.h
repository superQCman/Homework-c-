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
    // ѡ���Ѷȵķ���
    void selectDifficulty(int level);

private:
    cocos2d::Sprite* spriteD;
    cocos2d::Label* coinLabel; // ��ʾ��������ı�ǩ
    int level = 1;  // �Ѷȼ���
    cocos2d::Label* levelLabel;  // ������ʾ�Ѷȼ���ı�ǩ
};

#endif 

