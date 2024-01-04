#include "choose.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "store_message.h"
#include"Scene_one.h"
#include <fstream>

using namespace cocos2d;
USING_NS_CC;

Scene* Choose::createScene()
{
    return Choose::create();
}

bool Choose::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 获取屏幕的可视大小和起点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //设置背景
    auto background = Sprite::create("background_light.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // add the sprite as a child to this layer
    this->addChild(background, 0);


    // 添加难度选择图片
    auto addDifficultySprite = [&](const std::string& filename, float posX, int level) {
        auto sprite = Sprite::create(filename);
        sprite->setPosition(Vec2(posX, visibleSize.height * 0.75));
        this->addChild(sprite);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this, sprite, level](Touch* touch, Event* event) {
            if (sprite->getBoundingBox().containsPoint(touch->getLocation())) {
                this->selectDifficulty(level);
                return true;
            }
            return false;
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
    };

    auto addDifficultySprite2 = [&](const std::string& filename, float posX, int level) {
        auto sprite = Sprite::create(filename);
        sprite->setPosition(Vec2(posX, visibleSize.height * 0.25));
        this->addChild(sprite);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this, sprite, level](Touch* touch, Event* event) {
            if (sprite->getBoundingBox().containsPoint(touch->getLocation())) {
                if(level>3&&level<=5)this->selectDifficulty_2(level);
                else this->selectDifficulty_3(level);
                return true;
            }
            return false;
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
    };

    addDifficultySprite("intro_Matchstick man.png", visibleSize.width / 4, 1);
    addDifficultySprite("intro_Lightning Nick.png", visibleSize.width / 2, 2);
    addDifficultySprite("intro_chinchilla.png", visibleSize.width * 3 / 4, 3);

    addDifficultySprite2("intro_razor.png", visibleSize.width*0.2, 4);
    addDifficultySprite2("intro_Aegis.png", visibleSize.width *0.4, 5);
    addDifficultySprite2("intro_pencil.png", visibleSize.width*0.6, 6);
    addDifficultySprite2("intro_fireball.png", visibleSize.width*0.8, 7);

    auto posC1 = Vec2(visibleSize.width / 4, visibleSize.height * 5 / 8);
    auto posC2 = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8);
    auto posC3 = Vec2(visibleSize.width * 3 / 4, visibleSize.height * 5 / 8);
    auto posC4 = Vec2(visibleSize.width * 0.2, visibleSize.height * 1 / 8);
    auto posC5 = Vec2(visibleSize.width * 0.4, visibleSize.height * 1 / 8);
    auto posC6 = Vec2(visibleSize.width * 0.6, visibleSize.height * 1 / 8);
    auto posC7 = Vec2(visibleSize.width * 0.8, visibleSize.height * 1 / 8);




    // 创建并初始化新的图片精灵
    spriteD = Sprite::create("tick.png"); // 假设图片为 "tick.png"
    if (store_message::choosePlayer[0] == 1)spriteD->setPosition(posC1);
    else if (store_message::choosePlayer[1] == 1)spriteD->setPosition(posC2);
    else if (store_message::choosePlayer[2] == 1)spriteD->setPosition(posC3);
    this->addChild(spriteD);

    spriteD2 = Sprite::create("tick.png"); // 假设图片为 "tick.png"
    if (store_message::chooseWeapon[0] == 1)spriteD2->setPosition(posC4);
    else if (store_message::chooseWeapon[1] == 1)spriteD2->setPosition(posC5);
    this->addChild(spriteD2);

    spriteD3 = Sprite::create("tick.png"); // 假设图片为 "tick.png"
    if (store_message::chooseWeapon[2] == 1)spriteD3->setPosition(posC6);
    else if (store_message::chooseWeapon[3] == 1)spriteD3->setPosition(posC7);
    this->addChild(spriteD3);

    return_button = ui::Button::create("return.png", "return_click.png");
    return_button->setPosition(Vec2(visibleSize.width - return_button->getContentSize().width / 2, return_button->getContentSize().height / 2));
    this->addChild(return_button, 0);
    return_button->addClickEventListener([this](Ref* sender) {
        auto scene1 = Scene_one::createScene();
        Director::getInstance()->replaceScene(scene1);
        Director::getInstance()->resume();
        });

    return true;
}

void Choose::selectDifficulty(int level)
{

    // 根据当前的难度级别更新 spriteD 的位置
    Vec2 newPosition;
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (level == 1) {
        newPosition = Vec2(visibleSize.width / 4, visibleSize.height * 5 / 8);
        store_message::choosePlayer[0] = 1;
        store_message::choosePlayer[1] = 0;
        store_message::choosePlayer[2] = 0;
    }
    else if (level == 2) {
        newPosition = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8);
        store_message::choosePlayer[1] = 1;
        store_message::choosePlayer[0] = 0;
        store_message::choosePlayer[2] = 0;
    }
    else if (level == 3) {
        newPosition = Vec2(visibleSize.width * 3 / 4, visibleSize.height * 5 / 8);
        store_message::choosePlayer[2] = 1;
        store_message::choosePlayer[1] = 0;
        store_message::choosePlayer[0] = 0;
    }
    else
        newPosition = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8); // 默认位置
    ofstream FileOut("PaidPlayers.txt");
    for (auto& i : store_message::paidPlayer) {
        FileOut << i << " ";
    }
    FileOut << endl;
    for (auto& i : store_message::choosePlayer) {
        FileOut << i << " ";
    }
    FileOut.close();
    spriteD->setPosition(newPosition);

    CCLOG("Difficulty set to: %d", level);
}

void Choose::selectDifficulty_2(int level)
{

    // 根据当前的难度级别更新 spriteD 的位置
    Vec2 newPosition;
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (level == 4&& store_message::paidWeapon[0]==1) {
        newPosition = Vec2(visibleSize.width * 0.2, visibleSize.height * 1 / 8);
        store_message::chooseWeapon[0] = 1;
        store_message::chooseWeapon[1] = 0;
    }
    else if (level == 5 && store_message::paidWeapon[1] == 1) {
        newPosition = Vec2(visibleSize.width * 0.4, visibleSize.height * 1 / 8);
        store_message::chooseWeapon[1] = 1;
        store_message::chooseWeapon[0] = 0;
    }
    else {
        newPosition = Vec2(visibleSize.width * 0.2, visibleSize.height * 1 / 8);
    }
    ofstream FileOut2("weapon.txt");
    for (auto& i : store_message::paidWeapon) {
        FileOut2 << i << " ";
    }
    FileOut2 << endl;
    for (auto& i : store_message::chooseWeapon) {
        FileOut2 << i << " ";
    }
    FileOut2.close();
    spriteD2->setPosition(newPosition);

    CCLOG("Difficulty set to: %d", level);
}

void Choose::selectDifficulty_3(int level)
{
    
    Vec2 newPosition;
    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (level == 6) {
        newPosition = Vec2(visibleSize.width * 0.6, visibleSize.height * 1 / 8);
        store_message::chooseWeapon[2] = 1;
        store_message::chooseWeapon[3] = 0;
    }
    else if (level == 7) {
        newPosition = Vec2(visibleSize.width * 0.8, visibleSize.height * 1 / 8);
        store_message::chooseWeapon[3] = 1;
        store_message::chooseWeapon[2] = 0;
    }
    else {
        newPosition = Vec2(visibleSize.width * 0.6, visibleSize.height * 1 / 8);
    }
    ofstream FileOut2("weapon.txt");
    for (auto& i : store_message::paidWeapon) {
        FileOut2 << i << " ";
    }
    FileOut2 << endl;
    for (auto& i : store_message::chooseWeapon) {
        FileOut2 << i << " ";
    }
    FileOut2.close();
    spriteD3->setPosition(newPosition);

    CCLOG("Difficulty set to: %d", level);
}