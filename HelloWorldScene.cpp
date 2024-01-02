/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Scene_one.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include <fstream>
#include "store_message.h"
USING_NS_CC;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    std::ifstream inputFile("Coin.txt");
    std::string coin = "";
    inputFile>>coin;
    inputFile.close();
    if (coin == "")coin = "0";
    int Coin = std::stoi(coin);
    store_message::coin = Coin;
    std::ifstream inputFile2("weapon.txt");
    std::string W = "";
    for (int i = 0; i < 4; i++) {
        inputFile2 >> W;
        store_message::paidWeapon[i]= std::stoi(W);
    }
    for (int i = 0; i < 4; i++) {
        inputFile2 >> W;
        store_message::chooseWeapon[i]= std::stoi(W);
    }
    inputFile2.close();

    std::ifstream inputFile3("PaidPlayers.txt");
    for (int i = 0; i < 3; i++) {
        inputFile3 >> W;
        store_message::paidPlayer[i] = std::stoi(W);
    }
    for (int i = 0; i < 3; i++) {
        inputFile3 >> W;
        store_message::choosePlayer[i]= std::stoi(W);
    }
    inputFile3.close();

    std::ifstream inputFile4("degree.txt");
    W = "";
    inputFile4 >> W;
    if (W != "")store_message::DegreeOfDif = std::stoi(W);
    inputFile4.close();

    for (int i = 0; i < 3; i++) {
        if (store_message::choosePlayer[i] == 1)store_message::player = store_message::PlayerNames[i];
    }
    for (int i = 0; i < 2; i++) {
        if (store_message::chooseWeapon[i] == 1)store_message::wepon_second = store_message::WeaponNames[i];
    }
    for (int i = 2; i < 4; i++) {
        if (store_message::chooseWeapon[i] == 1)store_message::wepon_first = store_message::WeaponNames[i];
    }


    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto Title = Label::createWithTTF("Welcome to our world!", "fonts/Marker Felt.ttf", 75);
    //mylabel->enableShadow();
    if (Title == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        Title->enableShadow();
        Color4B customColor(255, 0, 0, 255);
        Title->setTextColor(customColor);
        // position the label on the center of the screen
        Title->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - Title->getContentSize().height));
        // add the label as a child to this layer
        this->addChild(Title, 1);
    }
    auto background = Sprite::create("background1.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 0);
    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("runrun-21.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("runrun-21.png");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
    /*auto changeItem = MenuItemImage::create("btn-play-normal.png",
        "btn-play-selected.png",
        CC_CALLBACK_1(HelloWorld::buttonCallback, this));
    changeItem->setPosition(Vec2(visibleSize.width - changeItem->getContentSize().width,
        changeItem->getContentSize().height));
    auto menu2 = Menu::create(changeItem, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);*/
    auto button1 = ui::Button::create("btn-play-normal.png", "btn-play-selected.png");
    button1->setPosition(Vec2(visibleSize.width/2,
        visibleSize.height / 2));
    float duration = 1.0f; // 动画持续时间

    // 定义缩放动作
    ScaleTo* scaleToBig = ScaleTo::create(duration, 2.0f); // 缩放到两倍大小
    ScaleTo* scaleToSmall = ScaleTo::create(duration, 1.5f); // 缩放回原大小

    // 定义序列动作
    Sequence* sequence = Sequence::create(scaleToBig, scaleToSmall, nullptr);

    // 将序列动作重复执行
    RepeatForever* repeatForever = RepeatForever::create(sequence);

    // 执行动作
    button1->runAction(repeatForever);
    this->addChild(button1, 0);
    button1->addClickEventListener([](Ref* sender) {
        AudioEngine::stopAll();
        auto scene1 = Scene_one::createScene();
        Director::getInstance()->replaceScene(scene1);
        });
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
//void HelloWorld::buttonCallback(cocos2d::Ref* pSender)
//{
//    // 创建并切换到新场景
//    auto newScene = Scene_one::createScene();
//    Director::getInstance()->replaceScene(newScene);
//}

int main() {
    return 0;
}
