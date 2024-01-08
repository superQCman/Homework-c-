#include "PoolScene.h"
#include "ui/CocosGUI.h"
#include"store_message.h"
#include"Scene_one.h"
#include"cocos2d.h"
#include<fstream>
using namespace cocos2d;

USING_NS_CC;

int coins=store_message::coin; // 引入外部全局变量coins

Scene* PoolScene::createScene() {
    return PoolScene::create();
}

bool PoolScene::init() {

    // 获取屏幕的可视大小和起点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建背景
    auto background = Sprite::create("background_light.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    // add the sprite as a child to this layer
    this->addChild(background, 0);
    //显示金币数
    std::string show = "Coin:" + std::to_string(store_message::coin);
    show_reward = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
    show_reward->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    show_reward->setColor(Color3B::RED);
    this->addChild(show_reward, 0);
    
    if (!Scene::init()) {
        return false;
    }
    this->n = 1;

    // 初始化并显示4张图片
    std::string initialFilenames[4]= { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };
    float upperQuarterY = visibleSize.height * 3 / 4 + origin.y; // 上方四分之一的Y坐标
    float lowerQuarterY = visibleSize.height * 1 / 4 + origin.y; // 下方四分之一的Y坐标

    for (int i = 0; i < 4; i++) {
        // 将a1到a5图片放在屏幕的上方四分之一
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
        // 为每个图片添加点击事件
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

    // 创建一个按钮
    auto returnButton = ui::Button::create();
    returnButton->setTitleText("Return");
    returnButton->setTitleFontSize(24);
    returnButton->setColor(Color3B::RED);

    // 设置按钮位置（屏幕右下角）
    //returnButton->setPosition(Vec2(visibleSize.width - returnButton->getContentSize().width / 2,
    //    returnButton->getContentSize().height / 2));
    // 设置按钮位置（屏幕中心）
    returnButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 12));

    // 添加按钮点击事件
    returnButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // 按钮点击后的逻辑，比如切换回主菜单
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
                // 设置透明度为0，使文本完全透明
                show_warning->setOpacity(0);
                // 创建渐变动画，从透明度0渐变到255，持续时间为1秒
                auto fadeAction = FadeIn::create(1.0f);
                auto delay = DelayTime::create(2.0f);
                auto fadeout = FadeOut::create(1.0f);

                auto sequenceAction = Sequence::create(fadeAction, delay, fadeout, nullptr);
                // 将动画应用于Label节点
                show_warning->runAction(sequenceAction);
            }
        }
    }
}


