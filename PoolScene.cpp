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
        std::string show = "";
        if (i < 2 && store_message::paidPlayer[i + 1] == 1 || i >= 2 && store_message::paidWeapon[(i - 1)*2-1]==1) {
            show = "All ready bought";
        }
        else
            show = std::to_string((i + 1) * 100)+" coins";
        auto show_price = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
        show_price->setPosition(Vec2(spriteArray[i]->getPosition().x, spriteArray[i]->getPosition().y- spriteArray[i] ->getContentSize().height/2 - show_price->getContentSize().height));
        show_price->setColor(Color3B::RED);
        this->addChild(show_price);
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
    returnButton->setColor(Color3B::RED);

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

    return true;
}

void PoolScene::spriteTouched(Ref* pSender, float lowerQuarterY) {
    const std::string alternateFilenames1[] = { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };
    const std::string alternateFilenames2[] = { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };

    for (int i = 0; i < 4; i++) {
        
        if (pSender == spriteArray[i]) {
            if(store_message::coin >= (i + 1) * 100 && (i < 2 && store_message::paidPlayer[i + 1] == 0 || i >= 2 && store_message::paidWeapon[(i - 1) * 2 - 1] == 0)){
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
                    store_message::paidWeapon[2*i - 3] = 1;
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
                ofstream FileOut3("Coin.txt");
                FileOut3 << store_message::coin;
                FileOut3.close();
                break;
            }
            if (store_message::coin < (i + 1) * 100 && (i < 2 && store_message::paidPlayer[i + 1] == 0 || i >= 2 && store_message::paidWeapon[(i - 1) * 2 - 1] == 0)) {
                std::string show = "Your coin is not enough";
                show_warning = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
                show_warning->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 850));
                show_warning->setColor(Color3B::RED);
                this->addChild(show_warning);
                // ����͸����Ϊ0��ʹ�ı���ȫ͸��
                show_warning->setOpacity(0);
                // �������䶯������͸����0���䵽255������ʱ��Ϊ1��
                auto fadeAction = FadeIn::create(1.0f);
                auto delay = DelayTime::create(2.0f);
                auto fadeout = FadeOut::create(1.0f);

                auto sequenceAction = Sequence::create(fadeAction, delay, fadeout, nullptr);
                // ������Ӧ����Label�ڵ�
                show_warning->runAction(sequenceAction);
            }
        }
    }
}


