#include "PoolScene.h"
#include "ui/CocosGUI.h"
#include"store_message.h"
#include"Scene_one.h"
#include"cocos2d.h"
#include<fstream>
using namespace cocos2d;

USING_NS_CC;

int coins=store_message::coin; // �����ⲿȫ�ֱ���coins

Scene* PoolScene::createScene() {
    return PoolScene::create();
}

bool PoolScene::init() {

    // ��ȡ��Ļ�Ŀ��Ӵ�С���������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //��������
    auto background = Sprite::create("background_light.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // add the sprite as a child to this layer
    this->addChild(background, 0);
    //��ʾ�����
    std::string show = "Coin:" + std::to_string(store_message::coin);
    show_reward = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
    show_reward->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    show_reward->setColor(Color3B::RED);
    this->addChild(show_reward, 0);
    
    if (!Scene::init()) {
        return false;
    }
    this->n = 1;

    // ��ʼ������ʾ4��ͼƬ
    std::string initialFilenames[4]= { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };
    float upperQuarterY = visibleSize.height * 3 / 4 + origin.y; // �Ϸ��ķ�֮һ��Y����
    float lowerQuarterY = visibleSize.height * 1 / 4 + origin.y; // �·��ķ�֮һ��Y����

    for (int i = 0; i < 4; i++) {
        // ��a1��a5ͼƬ������Ļ���Ϸ��ķ�֮һ
        spriteArray[i] = Sprite::create(initialFilenames[i]);
        spriteArray[i]->setPosition(visibleSize.width / 5 * (i + 1), upperQuarterY);
        this->addChild(spriteArray[i], 1);

        // Ϊÿ��ͼƬ��ӵ���¼�
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = [this, i, lowerQuarterY](Touch* touch, Event* event) -> bool {
            if (spriteArray[i]->getBoundingBox().containsPoint(touch->getLocation())) {
                this->spriteTouched(spriteArray[i], lowerQuarterY);
                return true;
            }
            return false;
         };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, spriteArray[i]);
    }

    // ����һ����ť
    auto returnButton = ui::Button::create();
    returnButton->setTitleText("Return");
    returnButton->setTitleFontSize(24);

    // ���ð�ťλ�ã���Ļ���½ǣ�
    //returnButton->setPosition(Vec2(visibleSize.width - returnButton->getContentSize().width / 2,
    //    returnButton->getContentSize().height / 2));
    // ���ð�ťλ�ã���Ļ���ģ�
    returnButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 12));

    // ��Ӱ�ť����¼�
    returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // ��ť�������߼��������л������˵�
            Director::getInstance()->replaceScene(Scene_one::createScene());
        }
        });

    this->addChild(returnButton);

    // ���� "check1" ��ť
    auto check1Button = ui::Button::create();
    check1Button->setTitleText("Left");
    check1Button->setTitleFontSize(24);
    check1Button->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 12)); // ���ð�ťλ��

    // ��Ӱ�ť����¼���ʹ�� Lambda ���ʽ��
    check1Button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->n = 1;
            // ����ͼƬΪ "a1.png" �� "a5.png"
            for (int i = 0; i < 4; i++) {
                std::string newFilename = "a" + std::to_string(i + 1) + ".png";
                spriteArray[i]->setTexture(newFilename);
            }
            // ��ͼƬ�ƶ�����Ļ�ϰ벿��
            float upperQuarterY = Director::getInstance()->getVisibleSize().height * 0.75;
            for (int i = 0; i < 4; i++) {
                spriteArray[i]->setPosition(spriteArray[i]->getPosition().x, upperQuarterY);
            }
        }
        });

    this->addChild(check1Button);

    // ���� "check2" ��ť
    auto check2Button = ui::Button::create();
    check2Button->setTitleText("Right");
    check2Button->setTitleFontSize(24);
    check2Button->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 12)); // ���ð�ťλ��

    // ��Ӱ�ť����¼���ʹ�� Lambda ���ʽ��
    check2Button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->n = 2;
            // ����ͼƬΪ "a6.png" �� "a10.png"
            for (int i = 0; i < 4; i++) {
                std::string newFilename = "a" + std::to_string(i + 6) + ".png";
                spriteArray[i]->setTexture(newFilename);
            }
            // ��ͼƬ�ƶ�����Ļ�ϰ벿��
            float upperQuarterY = Director::getInstance()->getVisibleSize().height * 0.75;
            for (int i = 0; i < 4; i++) {
                spriteArray[i]->setPosition(spriteArray[i]->getPosition().x, upperQuarterY);
            }
        }
    });

    this->addChild(check2Button);


    return true;
}

void PoolScene::spriteTouched(Ref* pSender, float lowerQuarterY) {
    const std::string alternateFilenames1[] = { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };
    const std::string alternateFilenames2[] = { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };

    for (int i = 0; i < 4; i++) {
        if (pSender == spriteArray[i]&& store_message::coin>=(i+1)*100) {
            std::string newFilename;
            if (n == 1) {
                newFilename = alternateFilenames1[i];
            }
            else if (n == 2) {
                newFilename = alternateFilenames2[i];
            }
            if (i < 2) { 
                store_message::paidPlayer[i + 1] = 1;
                store_message::coin -= (i + 1) * 100;
            }
            else {
                store_message::paidWeapon[i - 1] = 1;
                store_message::coin -= (i + 1) * 100;
            }
            std::string show = "Coin:" + std::to_string(store_message::coin);
            show_reward->setString(show);
            spriteArray[i]->setTexture(newFilename);
            spriteArray[i]->setPosition(spriteArray[i]->getPosition().x, lowerQuarterY);
            ofstream FileOut("PaidPlayers.txt");
            for (auto& i : store_message::paidPlayer) {
                FileOut << i << " ";
            }
            FileOut << endl;
            for (auto& i : store_message::choosePlayer) {
                FileOut << i << " ";
            }
            FileOut.close();
            ofstream FileOut2("weapon.txt");
            for (auto& i : store_message::paidWeapon) {
                FileOut2 << i << " ";
            }
            FileOut2 << endl;
            for (auto& i : store_message::chooseWeapon) {
                FileOut2 << i << " ";
            }
            FileOut2.close();
            break;
        }
    }
}


