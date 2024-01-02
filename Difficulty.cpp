#include "Difficulty.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "store_message.h"
#include"Scene_one.h"
#include <fstream>

using namespace cocos2d;
USING_NS_CC;

Scene* Difficulty::createScene()
{
    return Difficulty::create();
}

bool Difficulty::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 获取屏幕的可视大小和起点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //设置背景
    auto background = Sprite::create("background.png");

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

    addDifficultySprite("c1.png", visibleSize.width / 4, 1);
    addDifficultySprite("c2.png", visibleSize.width / 2, 2);
    addDifficultySprite("c3.png", visibleSize.width * 3 / 4, 3);

    auto posC1 = Vec2(visibleSize.width / 4, visibleSize.height * 5 / 8);
    auto posC2 = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8);
    auto posC3 = Vec2(visibleSize.width * 3 / 4, visibleSize.height * 5 / 8);
    // 初始化显示难度级别的标签
    levelLabel = Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 24);
    levelLabel->setPosition(Vec2(origin.x + levelLabel->getContentSize().width / 2,
        origin.y + visibleSize.height - levelLabel->getContentSize().height));
    this->addChild(levelLabel);

    // 创建并初始化新的图片精灵
    spriteD = Sprite::create("tick.png"); // 假设图片为 "tick.png"
    if(store_message::DegreeOfDif==2)spriteD->setPosition(posC1);
    else if (store_message::DegreeOfDif == 4)spriteD->setPosition(posC2);
    else if (store_message::DegreeOfDif == 6)spriteD->setPosition(posC3);
    this->addChild(spriteD);

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

void Difficulty::selectDifficulty(int level)
{
    this->level = level;
    // 更新显示难度级别的标签
    levelLabel->setString("Level: " + std::to_string(level));

    // 根据当前的难度级别更新 spriteD 的位置
    Vec2 newPosition;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    if(level==1){
        newPosition = Vec2(visibleSize.width / 4, visibleSize.height * 5 / 8);
        store_message::DegreeOfDif = 2;
    }
    else if (level == 2) {
        newPosition = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8);
        store_message::DegreeOfDif = 4;
    }
    else if (level == 3) {
        newPosition = Vec2(visibleSize.width * 3 / 4, visibleSize.height * 5 / 8);
        store_message::DegreeOfDif = 6;
    }
    else
        newPosition = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8); // 默认位置
    std::ofstream OutFile("degree.txt");
    OutFile << level*2;
    OutFile.close();
    spriteD->setPosition(newPosition);

    CCLOG("Difficulty set to: %d", level);
}






