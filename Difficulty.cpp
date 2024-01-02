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

    // ��ȡ��Ļ�Ŀ��Ӵ�С���������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //���ñ���
    auto background = Sprite::create("background.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // add the sprite as a child to this layer
    this->addChild(background, 0);


    // ����Ѷ�ѡ��ͼƬ
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
    // ��ʼ����ʾ�Ѷȼ���ı�ǩ
    levelLabel = Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 24);
    levelLabel->setPosition(Vec2(origin.x + levelLabel->getContentSize().width / 2,
        origin.y + visibleSize.height - levelLabel->getContentSize().height));
    this->addChild(levelLabel);

    // ��������ʼ���µ�ͼƬ����
    spriteD = Sprite::create("tick.png"); // ����ͼƬΪ "tick.png"
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
    // ������ʾ�Ѷȼ���ı�ǩ
    levelLabel->setString("Level: " + std::to_string(level));

    // ���ݵ�ǰ���Ѷȼ������ spriteD ��λ��
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
        newPosition = Vec2(visibleSize.width / 2, visibleSize.height * 5 / 8); // Ĭ��λ��
    std::ofstream OutFile("degree.txt");
    OutFile << level*2;
    OutFile.close();
    spriteD->setPosition(newPosition);

    CCLOG("Difficulty set to: %d", level);
}






