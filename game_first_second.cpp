#include "game_first_second.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "player.h"
#include <cstdlib>
#include"Barrier.h"
#include "AudioEngine.h"
#include"store_message.h"
#include<cmath>
#include <fstream>
using namespace cocos2d;
USING_NS_CC;


Scene* game_first_second::createScene() {
    return game_first_second::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void game_first_second::timerCallback(float dt) {
    static double time = 0;
    time += 1;
    for (auto i : Barrier_list) {
        if(!End)i->sprite->setPositionY(100 * sin(time)+i->pos.y);
    }
    // 在这里编写定时器任务要执行的代码
    CCLOG("Timer callback is called!");
}

bool game_first_second::init() {
    auto soundEffectID = AudioEngine::play2d("game_two_sound.mp3", true);
    barrier_num = store_message::DegreeOfDif/2;
    srand(time(0));
    scheduleUpdate();
    groundY = 80;
    string replacestr = store_message::background.substr(15);
    store_message::background.replace(15, replacestr.length(), "_black.png");
    background = Sprite::create(store_message::background);//设置背景
    this->addChild(background, 0);
    background->setPosition(Vec2(background->getContentSize().width / 2, visibleSize.height / 2));

    Land = Sprite::create("Land.png");//设置地面跑道
    float scaleX = visibleSize.width / Land->getContentSize().width;
    //Land->setScaleX(scaleX);
    Land->setPosition(Vec2(visibleSize.width / 2, 0));
    this->addChild(Land, 0);
    Land2 = Sprite::create("Land.png");
    //Land2->setScaleX(scaleX);
    Land2->setPosition(Vec2(visibleSize.width / 2 + visibleSize.width, 0));
    this->addChild(Land2, 0);
    auto barrier_ = AutoPolygon::generatePolygon("barrier.png");


    for (int i = 0;i < barrier_num*2;i++) {//篮球障碍物
        Barrier_base* barrier = new rocket("monster1-1(1).png");
        barrier->set_velocity(-200);
        barrier->set_position((i + 1) * 100, groundY);
        barrier->set_rand_num((7 + i * 3) / 6 + 5);
        Vector<SpriteFrame*> frames;
        for (int i = 1; i <= 7; i++) {
            SpriteFrame* frame= SpriteFrame::create("monster1-" + std::to_string(i) + "(1).png", Rect(0, 0, 300, 200)); // Set width and height here
            frames.pushBack(frame);
        }
        Animation* animation= Animation::createWithSpriteFrames(frames, 0.05f);
        Animate* animate= Animate::create(animation);
        RepeatForever* repeat= RepeatForever::create(animate);
        barrier->sprite->runAction(repeat);
        this->addChild(barrier->sprite, 0);
        Barrier_list.push_back(barrier);
    }
    for (int i = 0;i < barrier_num ;i++) {//篮球障碍物
        Barrier_base* barrier = new rocket_back("monster1-1(1).png");
        barrier->set_velocity(100);
        barrier->set_position((i + 1) * 100,groundY);
        barrier->set_rand_num((9 + i * 5) / 4 + 3);
        barrier->sprite->setScaleX(-1);
        Vector<SpriteFrame*> frames;
        for (int i = 1; i <= 7; i++) {
            SpriteFrame* frame = SpriteFrame::create("monster1-" + std::to_string(i) + "(1).png", Rect(0, 0, 300, 200)); // Set width and height here
            frames.pushBack(frame);
        }
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.05f);
        Animate* animate = Animate::create(animation);
        RepeatForever* repeat = RepeatForever::create(animate);
        barrier->sprite->runAction(repeat);
        this->addChild(barrier->sprite, 0);
        Barrier_back_list.push_back(barrier);
    }
    for (int i = 0;i < 4 * barrier_num;i++) {//金币
        Barrier_base* coin = new NotMove("coin_black.png");
        coin->set_velocity(-200);
        coin->set_position(i * 200, groundY);
        coin->sprite->setScale(0.5f);
        this->addChild(coin->sprite, 0);
        Coin_list.push_back(coin);
    }
    if (Barrier_list.size() != 0)Barrier_ALL.push_back(Barrier_list);
    if (Barrier_back_list.size() != 0)Barrier_ALL.push_back(Barrier_back_list);
    if (Barrier_NotMove_list.size() != 0)Barrier_ALL.push_back(Barrier_NotMove_list);



    string before = "", after = "";
    for (char i : store_message::player) {
        if (before.size() < 6)before += i;
        else after += i;
    }

    before.pop_back();
    fireboy = new Fireboy(groundY, store_message::player, before, after, 8, 1);//人物初始化
    fireboy->sprite->setScale(0.4f);
    fireboy->repeat = RepeatForever::create(fireboy->animate);
    fireboy->sprite->runAction(fireboy->repeat);
    fireboy->reward = store_message::coin;
    fireboy->sprite->setPositionX(-fireboy->sprite->getContentSize().width / 2);
    fireboy->ready = false;
    auto listener = EventListenerKeyboard::create();
    boss = new Teacher(groundY, "teacher-1.png", "teacher-", ".png",18,2);
    boss->repeat = RepeatForever::create(boss->animate);
    boss->sprite->runAction(boss->repeat);
    boss->sprite->setPositionX(boss->sprite->getContentSize().width / 2 + visibleSize.width);
    boss->ready = false;
    // 设置按键按下事件的响应函数
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        // 当按下D键时发射主武器
        if (keyCode == EventKeyboard::KeyCode::KEY_D && fireboy->reward >= 6) {
            // 在此处创建新的精灵
            std::string pic = "";
            auto soundEffectID = AudioEngine::play2d("fire.mp3", false);
            weapon* newSprite = nullptr;
            
            pic = store_message::wepon_first;
            fireboy->reward -= 6;
            newSprite = new pensil(pic);
            newSprite->WeponSize = 2;
            
           
            fireboy->throw_weapon(fireboy,pic,newSprite);//扔出武器
            // 将新的精灵添加到这个层 
            if(newSprite)this->addChild(newSprite->sprite, 1);
            Weapon.push_back(newSprite);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S && fireboy->reward >= 3) {//按下S键时发射副武器
            // 在此处创建新的精灵
            std::string pic = "";
            auto soundEffectID = AudioEngine::play2d("fire.mp3", false);
            weapon* newSprite = nullptr;

            pic = store_message::wepon_second;
            fireboy->reward -= 3;
            newSprite = new razor(pic);
            newSprite->WeponSize = 1;


            fireboy->throw_weapon(fireboy, pic, newSprite);//扔出武器
            // 将新的精灵添加到这个层 
            if (newSprite)this->addChild(newSprite->sprite, 1);
            Weapon.push_back(newSprite);
        }
    };

    // 将监听器与当前场景的事件分发器关联
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    schedule([=](float dt) {
        // 检查当前的帧
        size_t currentFrameIndex = boss->animate->getCurrentFrameIndex();
        if (currentFrameIndex == 1)BossWeponCheck = true;
        // 如果当前帧是你关心的帧，创建新的精灵
        if (currentFrameIndex == 15 && BossWeponCheck) {
            Barrier_base* newSprite = new rocket("flying-4.png");
            boss->throw_weapon(boss, "", newSprite);
            // 将新的精灵添加到这个层 
            this->addChild(newSprite->sprite, 1);
            Boss_weapon.push_back(newSprite);
            BossWeponCheck = false;
        }
        }, "check_animation_key");
    this->addChild(fireboy->sprite, 0);
    this->addChild(boss->sprite, 0);
    return_button = ui::Button::create("return.png", "return_click.png");
    return_button->setPosition(Vec2(visibleSize.width - return_button->getContentSize().width / 2, return_button->getContentSize().height / 2));
    this->addChild(return_button, 0);
    return_button->addClickEventListener([this](Ref* sender) {
        AudioEngine::stopAll();
        delete fireboy;
        fireboy = nullptr;
        auto scene1 = Scene_one::createScene();
        Director::getInstance()->replaceScene(scene1);
        Director::getInstance()->resume();
        });
    //显示金币数
    std::string show = "Coin:" + std::to_string(fireboy->reward);
    show_reward = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
    show_reward->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    
    //show_reward->setColor(Color3B::RED);
    this->addChild(show_reward, 0);
    //显示生命值
    std::string blood = "BLOOD:" + std::to_string(int(fireboy->blood_now / fireboy->blood * 100)) + "%";
    show_blood = Label::createWithTTF(blood, "fonts/Marker Felt.ttf", 55);
    show_blood->setPosition(Vec2(150, visibleSize.height - 150));
    //show_blood->setColor(Color3B::RED);
    this->addChild(show_blood, 0);
    //显示boss生命值
    std::string blood_ = "BOSS BLOOD:" + std::to_string(int(boss->blood_now / boss->blood * 100)) + "%";
    show_boss_blood = Label::createWithTTF(blood_, "fonts/Marker Felt.ttf", 45);
    show_boss_blood->setPosition(Vec2(visibleSize.width - 250, visibleSize.height - 350));
    show_boss_blood->setColor(Color3B::YELLOW);
    this->addChild(show_boss_blood, 0);
    //显示加速缓冲
    std::string accuracy = "Physical Fitness:" + std::to_string(int(fireboy->energy / fireboy->full_energy * 100)) + "%";
    show_accuracy = Label::createWithTTF(accuracy, "fonts/Marker Felt.ttf", 35);
    show_accuracy->setPosition(Vec2(150, visibleSize.height - 250));
    //show_accuracy->setColor(Color3B::RED);
    this->addChild(show_accuracy, 0);
    schedule(CC_SCHEDULE_SELECTOR(Game_first::update));
    setCloseItem();
    this->schedule(CC_SCHEDULE_SELECTOR(game_first_second::timerCallback), 0.1f);

    return true;
}

double y_velocity(Sprite* fireboy, Sprite* i, int x_velocity) {
    double Velocity_Y = (i->getPositionY() - fireboy->getPositionY() - 50) / abs(i->getPositionX() - fireboy->getPositionX()) * x_velocity*0.2;
    if (i->getPositionX() - fireboy->getPositionX() < 50)return 0;
    else return Velocity_Y;
}
void game_first_second::update(float delta) {
    if (fireboy&&!fireboy->ready) {
        auto move = MoveTo::create(0.5f, Vec2(fireboy->sprite->getContentSize().width * 2, groundY));
        fireboy->sprite->runAction(move);
        fireboy->ready=true;
    }
    if (boss&&!boss->ready) {
        auto move = MoveTo::create(1.5f, Vec2(visibleSize.width - boss->sprite->getContentSize().width * 1.5, groundY + 50));
        boss->sprite->runAction(move);
        boss->ready=true;
    }

    
    //显示金币数和血量
    if (fireboy) {
        store_message::coin = fireboy->reward;
        int blood_show = int(fireboy->blood_now / fireboy->blood * 100);
        if (blood_show < 0)blood_show = 0;
        if (boss && !boss->die && fireboy)fireboy->blood_now -= fireboy->blood * (-velocity * delta) / background->getContentSize().width;//在boss还活着的时候Fireboy要不断扣血
        std::string show = "Coin:" + std::to_string(fireboy->reward);
        show_reward->setString(show);
        std::string blood = "BLOOD:" + std::to_string(blood_show) + "%";
        show_blood->setString(blood);
        std::string accuracy = "Physical Fitness:" + std::to_string(int(fireboy->energy / fireboy->full_energy * 100)) + "%";
        show_accuracy->setString(accuracy);
        if (fireboy->blood_now <= 0) {
            auto soundEffectID = AudioEngine::play2d("game over.mp3", false);
            fireboy->sprite->stopAllActions();
            auto rotateTo = RotateTo::create(0, -150.0f);
            fireboy->sprite->runAction(rotateTo);
            auto endgame = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 65);
            //endgame->setColor(Color3B::RED);
            endgame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(endgame, 0);
            End = true;
            unschedule(CC_SCHEDULE_SELECTOR(Game_first::update));
        }
    }
    if (boss && !boss->die) {
        int blood_show = int(boss->blood_now / boss->blood * 100);
        if (blood_show < 0)blood_show = 0;
        std::string blood = "BOSS BLOOD:" + std::to_string(int(boss->blood_now / boss->blood * 100)) + "%";
        show_boss_blood->setString(blood);
        if (boss->blood_now <= 0) {
            show_boss_blood->removeFromParentAndCleanup(true);
            boss->sprite->setColor(Color3B::RED);
            boss->die = true;
            fireboy->reward += 50;
            boss->sprite->stopAllActions();
            this->removeChild(show_boss_blood);
            float duration = 1.0f;  // 旋转一周所需的时间
            auto rotateAction = RotateBy::create(duration, 360);

            // 创建无限循环动作
            auto repeatAction = RepeatForever::create(rotateAction);
            auto moveto = MoveTo::create(1, Vec2(visibleSize.width + boss->sprite->getContentSize().width, visibleSize.height + boss->sprite->getContentSize().height));
            // 应用动作到精灵
            boss->sprite->runAction(repeatAction);
            boss->sprite->runAction(moveto);
            boss->frames.clear();
            for (int i = 11; i <= 15; i++) {
                SpriteFrame* frame = SpriteFrame::create("teacher-" + std::to_string(i) + ".png", Rect(0, 0, 300, 260)); // Set width and height here
                boss->frames.pushBack(frame);
            }

            // Create the animation out of the frames
            boss->animation = Animation::createWithSpriteFrames(boss->frames, 0.05f);
            // Create an animate action from the animation
            boss->animate = Animate::create(boss->animation);
            auto repeat = Repeat::create(boss->animate, 3);
            boss->sprite->runAction(repeat);
        }
    }
    if (fireboy && !End) {

        int minVal = 100;
        int maxVal = 800;
        int randomNum = minVal + (rand() % (maxVal - minVal + 1));
        if (fireboy) {
            //防止小人卡bug掉出去
            if (fireboy->sprite->getPositionY() < groundY) {
                fireboy->sprite->setPositionY(groundY);
            }
            if (fireboy->jump_max < 4)
                temp++;
            if (temp == 90) {
                fireboy->jump_max += 1;
                temp = 0;
            }
            if (fireboy->jump_max < 2) {
                std::string show = "Jump too many times in a short period will make the character miss the runway,\n pressing the down arrow key to reset";
                show_warning = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
                show_warning->setColor(Color3B::RED);
                show_warning->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
                this->addChild(show_warning);
                // 设置透明度为0，使文本完全透明
                /* show_warning->setOpacity(0);*/
                // 创建渐变动画，从透明度0渐变到255，持续时间为1秒
                auto fadeAction = FadeIn::create(1.0f);
                auto delay = DelayTime::create(2.0f);
                auto fadeout = FadeOut::create(1.0f);
                auto sequenceAction = Sequence::create(delay, fadeout, nullptr);
                // 将动画应用于Label节点
                show_warning->runAction(sequenceAction);
            }
            if (!fireboy->faster && fireboy->sleep == 0) {
                fireboy->time += 1;
                fireboy->energy -= fireboy->full_energy / fireboy->get_accuracy_time();
            }
            if (fireboy->time >= fireboy->get_accuracy_time()) {
                fireboy->sleep += 1;
                fireboy->time = 0;
                stopAction(fireboy->repeat);
                fireboy->animation = Animation::createWithSpriteFrames(fireboy->frames, 0.05f);
                fireboy->animate = Animate::create(fireboy->animation);
                fireboy->repeat = RepeatForever::create(fireboy->animate);
                fireboy->sprite->runAction(fireboy->repeat);
                velocity2 /= 2;velocity /= 1.5;velocity_back *= 4;velocity_barrier /= 2;
                for (auto i : Barrier_NotMove_list) {
                    i->velocity /= 2;
                }
                for (auto i : Coin_list) {
                    i->velocity /= 2;
                }
                for (auto i : Barrier_list) {
                    i->velocity /= 2;
                }
                for (auto i : Barrier_back_list) {
                    i->velocity *= 4;
                    isKeyR = true;
                }
            }
            if (fireboy->sleep > fireboy->get_sleep_time()) {
                fireboy->faster = true;
                fireboy->sleep = 0;
            }
            else if (fireboy->sleep > 0) {
                fireboy->sleep += 1;
                fireboy->energy += fireboy->full_energy / fireboy->get_sleep_time();
            }

            //if (!fireboy->smaller && fireboy->small_sleep < fireboy->get_small_sleep_time()) {
            //    fireboy->small_sleep += 1;
            //}
            //else if (fireboy->small_sleep == fireboy->get_small_sleep_time()) {
            //    fireboy->small_sleep = 0;
            //    fireboy->smaller = true;
            //}
            
            barrier_list.clear();
            coin_list.clear();
            wepon_list.clear();
            BossWeapon.clear();
            barrier_list_origin.clear();
            for (auto& i : Barrier_ALL) {
                for (auto& j : i) {
                    if (j->sprite != nullptr) {
                        barrier_list.push_back(j->sprite->getBoundingBox());
                        barrier_list_origin.push_back(j);
                    }
                }
            }
            for (auto& i : Coin_list) {
                if (i->sprite != nullptr)
                    coin_list.push_back(i->sprite->getBoundingBox());
            }
            for (auto& i : Weapon) {
                if (i&&i->sprite != nullptr)
                    wepon_list.push_back(i->sprite->getBoundingBox());
            }
            for (auto& i : Boss_weapon) {
                if (i->sprite != nullptr)
                    BossWeapon.push_back(i->sprite->getBoundingBox());
            }

            auto fire_b = fireboy->sprite->getBoundingBox();
            auto boss_b = boss->sprite->getBoundingBox();
            if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 850) {
                for (int i = 0;i < barrier_list.size();i++) {
                    if (fire_b.intersectsRect(barrier_list[i]) && fireboy->sprite->getPositionX() < visibleSize.width + fireboy->sprite->getContentSize().width - 50 && 
                        fireboy->sprite->getPositionX()>0) {
                        // 两个物体相碰
                        // 进行处理，比如发生事件或执行某些动作
                        Vec2 position = Vec2(fireboy->sprite->getPosition().x + fireboy->sprite->getContentSize().width / 2.5f,
                            fireboy->sprite->getPosition().y);
                        auto boom = Game_first::Boom(position);
                        this->addChild(boom);
                        //if(!barrier_list_origin[i]->interaction)
                        fireboy->blood_now -= 5;
                        /*barrier_list_origin[i]->interaction = true;*/
                        auto action = Blink::create(0.5, 3);      // 创建一个Blink动作，持续2秒钟，闪烁10次
                        auto callback = CallFunc::create([&]() {
                            show_blood->setVisible(true);        // 确保闪烁结束后精灵是可见的
                            });
                        auto sequence = Sequence::create(action, callback, nullptr);   // 创建一个Sequence动作，先执行Blink，然后执行callback
                        show_blood->runAction(sequence);

                        barrier_list_origin[i]->sprite->setPositionX(2560 / 2 + 2560 + barrier_list_origin[i]->sprite->getPositionX() * 2);
                    }
                }
            }

            for (int i = 0;i < coin_list.size();i++){
                if (fire_b.intersectsRect(coin_list[i]) && fireboy->sprite->getPositionX() < visibleSize.width + fireboy->sprite->getContentSize().width - 50) {
                    // 两个物体相碰
                    // 进行处理，比如发生事件或执行某些动作
                    fireboy->reward += 2;
                    auto soundEffectID = AudioEngine::play2d("reward.mp3", false);
                    if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 550)
                        Coin_list[i]->sprite->setPosition(Vec2(visibleSize.width + Coin_list[i]->sprite->getContentSize().width, 200 + randomNum));
                    else
                        Coin_list[i]->sprite->setPositionX(-visibleSize.width - Coin_list[i]->sprite->getContentSize().width);
                }
            }
            for (int i = 0;i < wepon_list.size();i++) {
                if (boss_b.intersectsRect(wepon_list[i])) {
                    Vec2 position = Vec2(Weapon[i]->sprite->getPosition().x + Weapon[i]->sprite->getContentSize().width / 2,
                        Weapon[i]->sprite->getPosition().y);
                    auto boom2 = Game_first::Boom(position);
                    this->addChild(boom2);
                    boss->blood_now -= Weapon[i]->distroy_num*10;
                    
                    this->removeChild(Weapon[i]->sprite);
                    for (int z = i;z < Weapon.size() - 1;z++) {
                        Weapon[z] = Weapon[z + 1];
                    }
                    Weapon.pop_back();
                }

                for (int j = 0;j < barrier_list.size();j++) {
                    if (wepon_list[i].intersectsRect(barrier_list[j])) {
                        Vec2 position = Vec2(Weapon[i]->sprite->getPosition().x + Weapon[i]->sprite->getContentSize().width / 2,
                            Weapon[i]->sprite->getPosition().y);
                        auto boom2 = Game_first::Boom(position);
                        this->addChild(boom2);
                        barrier_list_origin[j]->sprite->setPositionX(2560 / 2 + 2560 + barrier_list_origin[j]->sprite->getPositionX() * 2);
                        Weapon[i]->distroy_num--;
                        if (Weapon[i]->distroy_num == 0) {
                            this->removeChild(Weapon[i]->sprite);
                            for (int z = i;z < Weapon.size() - 1;z++) {
                                Weapon[z] = Weapon[z + 1];
                            }
                            Weapon.pop_back();
                        }
                    }
                }
            }
            for (int i = 0;i < BossWeapon.size();i++) {
                if (fire_b.intersectsRect(BossWeapon[i]) && fireboy->sprite->getPositionX() < visibleSize.width + fireboy->sprite->getContentSize().width - 50) {
                    Vec2 position = Vec2(fireboy->sprite->getPosition().x + fireboy->sprite->getContentSize().width / 2.5f,
                        fireboy->sprite->getPosition().y);
                    auto boom = Game_first::Boom(position);
                    this->addChild(boom);
                    fireboy->blood_now -= 10;
                    auto action = Blink::create(0.5, 3);      // 创建一个Blink动作，持续2秒钟，闪烁10次
                    auto callback = CallFunc::create([&]() {
                        show_blood->setVisible(true);        // 确保闪烁结束后精灵是可见的
                        });
                    auto sequence = Sequence::create(action, callback, nullptr);   // 创建一个Sequence动作，先执行Blink，然后执行callback
                    show_blood->runAction(sequence);
                    this->removeChild(Boss_weapon[i]->sprite);
                    for (int z = i;z < Boss_weapon.size() - 1;z++) {
                        Boss_weapon[z] = Boss_weapon[z + 1];
                    }
                    Boss_weapon.pop_back();
                }
            }
            Size visibleSize = Director::getInstance()->getVisibleSize();
        }


        // 滚动背景精灵的位置
        background->setPosition(background->getPosition() + Vec2(velocity * delta, 0));
        Land->setPosition(Land->getPosition() + Vec2(velocity2 * delta, 0));
        Land2->setPosition(Land2->getPosition() + Vec2(velocity2 * delta, 0));
        if (fireboy)
            fireboy->sprite->setPosition(fireboy->sprite->getPosition() + Vec2(fireboy->velocity_player * delta * 2, 0));
        for (auto &i : Weapon) {
            if (i->sprite->getPositionX() >= visibleSize.width + i->sprite->getContentSize().width || i->sprite->getPositionX() <= -i->sprite->getContentSize().width) {
                this->removeChild(i->sprite);
                Weapon.pop_front();
            }
        }
        for (auto &i : Boss_weapon) {
            if (i->sprite->getPositionX() >= visibleSize.width + i->sprite->getContentSize().width || i->sprite->getPositionX() <= -i->sprite->getContentSize().width) {
                this->removeChild(i->sprite);
                Boss_weapon.pop_front();
            }
        }
        for (auto &i : Weapon) {
            i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta * 2, 0));
        }
        if (background->getPositionX() <= 3000) {
            for (auto i : Barrier_list) {
                if (randomNum % i->rand_num == 0)
                    i->rand_barrier = true;
                if (i->rand_barrier)
                    i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta * 2, 0));
            }
        }
        if (background->getPositionX() <= 2000) {
            for (auto i : Barrier_back_list) {
                if (randomNum % i->rand_num == 0)
                    i->rand_barrier = true;
                if (i->rand_barrier)
                    i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta * 2, 0));
                double a = i->sprite->getPositionX();
                double b = i->sprite->getPositionX();
            }
        }
        for (auto i : Barrier_NotMove_list) {

            if (randomNum % i->rand_num == 0)
                i->rand_barrier = true;
            if (i->rand_barrier)
                i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta, 0));
        }
        for (auto i : Coin_list) {
            i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta, 0));
        }
        for (auto i : Boss_weapon) {
            double velocity_y = y_velocity(fireboy->sprite, i->sprite, i->velocity);
            i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta, velocity_y*delta));
        }
        if (background->getPositionX() + background->getContentSize().width / 2 <= visibleSize.width + 10) {
            velocity = 0, velocity2 = 0;
            if (boss->blood_now <= 0)fireboy->velocity_player = 200;
        }
        if (fireboy && fireboy->sprite->getPositionX() > visibleSize.width + fireboy->sprite->getContentSize().width && boss->blood_now<=0) {
            auto soundEffectID = AudioEngine::play2d("congratulation.mp3", false);
            auto endgame = Label::createWithTTF("Successful!", "fonts/Marker Felt.ttf", 65);
            endgame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(endgame, 0);
            // 设置透明度为0，使文本完全透明
            endgame->setOpacity(0);
            // 创建渐变动画，从透明度0渐变到255，持续时间为1秒
            auto fadeAction = FadeIn::create(1.0f);
            // 将动画应用于Label节点
            endgame->runAction(fadeAction);
            End = true;
            unschedule(CC_SCHEDULE_SELECTOR(Game_first::update));
        }

        if (Land->getPositionX() < -Land->getContentSize().width / 2) {
            Land->setPositionX(visibleSize.width + Land->getContentSize().width / 2 - 10);
        }
        if (Land2->getPositionX() < -Land->getContentSize().width / 2) {
            Land2->setPositionX(visibleSize.width + Land->getContentSize().width / 2 - 10);
        }

        if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 1050) {
            for (auto i : Coin_list) {
                if (i->sprite->getPositionX() < -i->sprite->getContentSize().width) {
                    i->sprite->setPositionX(visibleSize.width + i->sprite->getContentSize().width);
                    i->rand_barrier = false;
                    i->interaction = false;
                }
            }
            for (auto i : Barrier_list) {
                if (i->sprite->getPositionX() < -i->sprite->getContentSize().width / 2) {
                    i->sprite->setPosition(Vec2(visibleSize.width + i->sprite->getContentSize().width / 2, 50 + randomNum));
                    i->rand_barrier = false;
                    i->interaction = false;
                }
            }

            for (auto i : Barrier_back_list) {
                if (i->sprite->getPositionX() > visibleSize.width + i->sprite->getContentSize().width / 2) {
                    i->sprite->setPosition(Vec2(-i->sprite->getContentSize().width, 200 + randomNum));
                    i->rand_barrier = false;
                    i->interaction = false;
                }

            }
        }
    }
    if (End) {
        for (auto i : Weapon) {
            this->removeChild(i->sprite);
            
        }
        for (auto &i : Barrier_list) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
        for (auto &i : Barrier_back_list) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
        for (auto &i : Barrier_NotMove_list) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
        for (auto &i : Coin_list) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        }
        pause++;
    }
    if (pause == 180) {
        AudioEngine::stopAll();
        /*auto scene1 = Game_first::createScene();
        Director::getInstance()->replaceScene(scene1);*/
        Director::getInstance()->pause();
    }

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(game_first_second::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(game_first_second::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}


void game_first_second::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){

    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !End && !isKeyUpUp) {
        if (!isKeyUp && fireboy->jump_max > 0) {
            isKeyUp = true;
            fireboy->Jump(groundY);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !End) {
        if (!isKeyD) {
            isKeyD = true;
            fireboy->Move(groundY);

        }
    }

    else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !End && !isKeyUp) {
        if (!isKeyUpUp && fireboy->jump_max > 0) {
            isKeyUpUp = true;
            fireboy->BigJump(groundY);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !isKeyR && !End && fireboy->faster) {
        fireboy->faster = false;
        //fireboy->run();
        stopAction(fireboy->repeat);
        fireboy->animation = Animation::createWithSpriteFrames(fireboy->frames, 0.03f);
        fireboy->animate = Animate::create(fireboy->animation);
        fireboy->repeat = RepeatForever::create(fireboy->animate);
        fireboy->sprite->runAction(fireboy->repeat);
        velocity2 *= 2;velocity *= 1.5;velocity_back /= 4;velocity_barrier *= 2;
        for (auto i : Barrier_NotMove_list) {
            i->velocity *= 2;
        }
        for (auto i : Coin_list) {
            i->velocity *= 2;
        }
        for (auto i : Barrier_list) {
            i->velocity *= 2;
        }

        for (auto i : Barrier_back_list) {
            i->velocity /= 4;
        }
        for (auto i : Boss_weapon) {
            i->velocity *= 2;
        }
        isKeyR = true;
    }
    //else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !isKeyL)
    //{
    //    // 判断键盘右键头键是否已按下
    //    auto move_by = MoveBy::create(0.5, Vec2(-40, 0));
    //    auto sequenceAction = Sequence::create(move_by, nullptr);
    //    auto repeatAction = RepeatForever::create(sequenceAction);
    //    //// 精灵开始跑动动作
    //    fireboy->runAction(repeatAction);
    //    move_L = repeatAction;
    //    isKeyL = true;
    //}
}

void game_first_second::onDelayEnded(float dt) {
    isKeyUpUp = false;
}
// 键盘抬起事件回调函数
void game_first_second::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        if (isKeyR) {
            isKeyR = false;
        }
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
        if (isKeyD) {
            isKeyD = false;
        }
    }
    //if (keyCode == EventKeyboard::KeyCode::KEY_D) {
    //    if (isKeyCD) {
    //        isKeyCD = false;
    //    }
    //}
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
        if (isKeyUp) {
            isKeyUp = false;
        }
        if (isKeyUpUp) {
            isKeyUpUp = false;
        }
    }
}
void game_first_second::menuCloseCallback(Ref* pSender)
{
    store_message::coin = fireboy->reward;
    std::ofstream outputFile("Coin.txt");
    outputFile << store_message::coin << endl;
    outputFile.close();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}