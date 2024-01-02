#include "Scene_one.h"
#include "Scene_one.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "Game_first.h"
#include"game_first_second.h"
#include"store_message.h"
#include "AudioEngine.h"
#include <fstream>
#include"Difficulty.h"
#include"PoolScene.h"
#include"choose.h"
using namespace cocos2d;
USING_NS_CC;
Scene* Scene_one::createScene()
{
    return Scene_one::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Scene_one::setCloseItem() {
    closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Scene_one::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}
bool Scene_one::init() {
    for (int i = 0; i < 3; i++) {
        if (store_message::choosePlayer[i] == 1)store_message::player = store_message::PlayerNames[i];
    }
    for (int i = 0; i < 2; i++) {
        if (store_message::chooseWeapon[i] == 1)store_message::wepon_second = store_message::WeaponNames[i];
    }
    for (int i = 2; i < 4; i++) {
        if (store_message::chooseWeapon[i] == 1)store_message::wepon_first = store_message::WeaponNames[i];
    }
    auto soundEffectID = AudioEngine::play2d("Start.mp3", true);
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
    labelConfig.fontSize = 45;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;
    setCloseItem();
    auto label = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 65);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    background = Sprite::create("background.png");
    background2 = Sprite::create("background.png");
    background2->setPosition(Vec2(visibleSize.width / 2 + visibleSize.width, visibleSize.height / 2));
    this->addChild(background2, 0);
    if (background == nullptr)
    {
        problemLoading("'background.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

        // add the sprite as a child to this layer
        this->addChild(background, 0);
        velocity = -100;
        schedule(CC_SCHEDULE_SELECTOR(Scene_one::update));
    }
    auto myList = { Label::createWithTTF(labelConfig, "First mode    "),Label::createWithTTF(labelConfig, "Second mode "),
    Label::createWithTTF(labelConfig, "Store       "), Label::createWithTTF(labelConfig,"Setting    "),Label::createWithTTF(labelConfig,"Warehouse  ") };
    std::vector<ui::Button*> Buttons = { ui::Button::create("btn-play-normal.png", "btn-play-selected.png") ,
        ui::Button::create("btn-play-normal.png", "btn-play-selected.png") ,
        ui::Button::create("Shop2.png", "Shop2-2.png"),
        ui::Button::create("setting1-2.png","setting1-1.png"),ui::Button::create("shop.png", "shop-2.png") };
    int pos = 1;
    for (auto element : myList) {

        if (element == nullptr)
        {
            problemLoading("'Words erro'");
        }
        else
        {
            // position the sprite on the center of the screen
            element->setPosition(Vec2(label->getPosition().x, label->getPosition().y - element->getPosition().y - pos * 200));
            this->addChild(element, 0);
            auto button1 = Buttons[pos - 1];
            button1->setPosition(Vec2(element->getPosition().x + element->getContentSize().width / 2 + button1->getContentSize().width / 2, element->getPosition().y));
            this->addChild(button1);
            pos++;
        }
    }
    //显示金币数
    std::string show = "Coin:" + std::to_string(store_message::coin);
    show_reward = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
    show_reward->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    //show_reward->setColor(Color3B::RED);
    this->addChild(show_reward, 0);
    Buttons[0]->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene1 = Game_first::createScene();
        Director::getInstance()->replaceScene(scene1);
        });
    Buttons[1]->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene2 = game_first_second::createScene();
        Director::getInstance()->replaceScene(scene2);
        });
    Buttons[2]->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene3 = PoolScene::createScene();
        Director::getInstance()->replaceScene(scene3);
        });
    Buttons[3]->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene4 = Difficulty::createScene();
        Director::getInstance()->replaceScene(scene4);
        });
    Buttons[4]->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene5 = Choose::createScene();
        Director::getInstance()->replaceScene(scene5);
        });
    return true;
}

void Scene_one::menuCloseCallback(Ref* pSender)
{
    std::ofstream outputFile("Coin.txt");
    outputFile << store_message::coin << endl;
    outputFile.close();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
void Scene_one::update(float delta)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 滚动背景精灵的位置
    background->setPosition(background->getPosition() + Vec2(velocity * delta, 0));
    background2->setPosition(background2->getPosition() + Vec2(velocity * delta, 0));
    // 当背景精灵滚动到一个阈值时，重置其位置
    if (background->getPositionX() < -background->getContentSize().width / 2) {
        background->setPositionX(visibleSize.width + background->getContentSize().width / 2 - 10);
    }
    if (background2->getPositionX() < -background2->getContentSize().width / 2) {
        background2->setPositionX(visibleSize.width + background2->getContentSize().width / 2 - 10);
    }
}