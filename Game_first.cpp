#include "Game_first.h"
#include"cocos2d.h"
#include "Scene_one.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "player.h"
#include <cstdlib>
#include"Barrier.h"
#include "AudioEngine.h"
#include"store_message.h"
#include"game_first_second.h"
#include <fstream>

using namespace cocos2d;
USING_NS_CC;

//���ñ�ըЧ��
Sprite* Game_first::Boom(cocos2d::Vec2 position) {
    auto soundEffectID = AudioEngine::play2d("boom.mp3", false);
    auto sprite = Sprite::create("Boom-1.png");
    // Position the sprite at the center of the screen
    sprite->setPosition(position);

    // Add the sprite as a child to this layer
    Vector<SpriteFrame*> frames;
    // Add frames to the vector
    for (int i = 1; i <= 5; i++) {
        auto frame = SpriteFrame::create("Boom-" + std::to_string(i) + ".png", Rect(0, 0, 300, 200)); // Set width and height here
        frames.pushBack(frame);
    }
    sprite->setScale(0.5f);
    // Create the animation out of the frames
    auto animation = Animation::createWithSpriteFrames(frames, 0.04f);

    // Create an animate action from the animation
    auto animate = Animate::create(animation);

    // ����һ���ص����������ӳ�ʱ���ɾ������
    auto remove = CallFunc::create([sprite]() {
        sprite->removeFromParentAndCleanup(true);
        });

    // ���Ŷ�����ɾ������
    auto sequence = Sequence::create(animate, remove, nullptr);
    sprite->runAction(sequence);

    // ��Sprite��ӵ�������
    return sprite;
}
// �������������
bool isKeyR = false, isKeyUp = false, isKeyUpUp = false, isKeyL = false, isKeyD = false, isKeyCD = false;
int replace_ = 0;
Scene* Game_first::createScene() {
    return Game_first::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Game_first::init() {
    auto soundEffectID = AudioEngine::play2d("Game.mp3", true);
    barrier_num = store_message::DegreeOfDif;
    srand(time(0));
    scheduleUpdate();
    groundY = 80;
    background = Sprite::create(store_message::background);//���ñ���
    this->addChild(background, 0);
    background->setPosition(Vec2(background->getContentSize().width / 2, visibleSize.height / 2));

    Land = Sprite::create("Land.png");//���õ����ܵ�
    float scaleX = visibleSize.width / Land->getContentSize().width;
    //Land->setScaleX(scaleX);
    Land->setPosition(Vec2(visibleSize.width / 2, 0));
    this->addChild(Land, 0);
    Land2= Sprite::create("Land.png");
    //Land2->setScaleX(scaleX);
    Land2->setPosition(Vec2(visibleSize.width / 2 + visibleSize.width, 0));
    this->addChild(Land2, 0);
    auto barrier_ = AutoPolygon::generatePolygon("barrier.png");

    
    for (int i = 0;i < barrier_num;i++) {//�����ϰ���
        Barrier_base* barrier = new rocket("laoda.png");
        barrier->set_velocity(-200);
        barrier->set_position((i + 1) * 100,groundY);
        barrier->set_rand_num((7 + i*3)/6+5);
        float duration = 1.0f;  // ��תһ�������ʱ��
        auto rotateAction = RotateBy::create(duration, 360);

        // ��������ѭ������
        auto repeatAction = RepeatForever::create(rotateAction);

        // Ӧ�ö���������
        barrier->sprite->runAction(repeatAction);
        this->addChild(barrier->sprite, 0);
        Barrier_list.push_back(barrier);
    }
    for (int i = 0;i < barrier_num-2;i++) {//�����ϰ���
        Barrier_base* barrier = new rocket_back("laoda.png");
        barrier->set_velocity(100);
        barrier->set_position((i + 1) * 100,groundY);
        barrier->set_rand_num((9 + i*5)/4+3);
        this->addChild(barrier->sprite, 0);
        Barrier_back_list.push_back(barrier);
    }
    for (int i = 0;i < barrier_num;i++) {//�̶��ϰ���
        Barrier_base* barrier = new NotMove("Dangang.png");
        auto rect = Rect(97, 0, 480, 280);
        barrier->sprite->setTextureRect(rect);
        barrier->set_velocity(-200);
        barrier->set_position((i + 1)*500,groundY);
        barrier->set_rand_num((8 + i*2)/3+7);
        barrier->sprite->setScale(0.5f);
        barrier->swing();
        this->addChild(barrier->sprite, 1);
        
        Barrier_NotMove_list.push_back(barrier);
    }
    for (int i = 0;i < 3*barrier_num;i++) {//���
        Barrier_base* coin = new NotMove("coin.png");
        coin->set_velocity(-200);
        coin->set_position(i*200,groundY);
        coin->sprite->setScale(0.5f);
        this->addChild(coin->sprite, 0);
        Coin_list.push_back(coin);
    }
    //for (int i = 0;i < 4;i++) {
    //    Barrier_base* barrier = new NotMove("coin.png");
    //    barrier->set_velocity();
    //}
    if(Barrier_list.size()!=0)Barrier_ALL.push_back(Barrier_list);
    if (Barrier_back_list.size() != 0)Barrier_ALL.push_back(Barrier_back_list);
    if (Barrier_NotMove_list.size() != 0)Barrier_ALL.push_back(Barrier_NotMove_list);

    //��store_message���л�ȡ�����ַ���
    string before = "", after = "";
    for (char i : store_message::player) {
        if (before.size() < 6)before += i;
        else after += i;
    }
    before.pop_back();
    if(store_message::choosePlayer[0]==1)fireboy = new Fireboy(groundY,store_message::player,before, after,8,1);//�����ʼ��
    else if(store_message::choosePlayer[1] == 1)fireboy = new Fox(groundY, store_message::player, before, after, 8, 1);//�����ʼ��
    else if (store_message::choosePlayer[2] == 1)fireboy = new Rat(groundY, store_message::player, before, after, 8, 1);//�����ʼ��
    fireboy->sprite->setScale(0.4f);
    fireboy->repeat = RepeatForever::create(fireboy->animate);
    fireboy->sprite->runAction(fireboy->repeat);
    auto listener = EventListenerKeyboard::create();

    // ���ð��������¼�����Ӧ����
    listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        // ������D��ʱ����������
        if (keyCode == EventKeyboard::KeyCode::KEY_D && fireboy->reward >= 6) {
            // �ڴ˴������µľ���
            std::string pic = "";
            auto soundEffectID = AudioEngine::play2d("fire.mp3", false);
            weapon* newSprite = nullptr;

            pic = store_message::wepon_first;
            fireboy->reward -= 6;
            newSprite = new pensil(pic);
            newSprite->WeponSize = 2;


            fireboy->throw_weapon(fireboy, pic, newSprite);//�ӳ�����
            // ���µľ�����ӵ������ 
            if (newSprite)this->addChild(newSprite->sprite, 1);
            Weapon.push_back(newSprite);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S && fireboy->reward >= 3) {//����S��ʱ���丱����
            // �ڴ˴������µľ���
            std::string pic = "";
            auto soundEffectID = AudioEngine::play2d("fire.mp3", false);
            weapon* newSprite = nullptr;

            pic = store_message::wepon_second;
            fireboy->reward -= 3;
            newSprite = new razor(pic);
            newSprite->WeponSize = 1;


            fireboy->throw_weapon(fireboy, pic, newSprite);//�ӳ�����
            // ���µľ�����ӵ������ 
            if (newSprite)this->addChild(newSprite->sprite, 1);
            Weapon.push_back(newSprite);
        }
    };

    // ���������뵱ǰ�������¼��ַ�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

         


    this->addChild(fireboy->sprite, 0);
    fireboy->reward = store_message::coin;
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
    //��ʾ�����
    std::string show = "Coin:" + std::to_string(fireboy->reward);
    show_reward = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
    show_reward->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
    show_reward->setColor(Color3B::RED);
    this->addChild(show_reward, 0);
    //��ʾ����ֵ
    std::string blood = "BLOOD:" + std::to_string(int(fireboy->blood_now / fireboy->blood * 100)) + "%";
    show_blood = Label::createWithTTF(blood, "fonts/Marker Felt.ttf", 55);
    show_blood->setPosition(Vec2(150, visibleSize.height - 150));
    show_blood->setColor(Color3B::RED);
    this->addChild(show_blood, 0);
    //��ʾ���ٻ���
    std::string accuracy = "Physical Fitness:" + std::to_string(int(fireboy->energy / fireboy->full_energy * 100)) + "%";
    show_accuracy = Label::createWithTTF(accuracy, "fonts/Marker Felt.ttf", 35);
    show_accuracy->setPosition(Vec2(150, visibleSize.height - 250));
    show_accuracy->setColor(Color3B::RED);
    this->addChild(show_accuracy, 0);
    schedule(CC_SCHEDULE_SELECTOR(Game_first::update));
    setCloseItem();
    return true;
}


JumpBy* Uper, * heigh_uper;RepeatForever* move, * move_L;int temp = 0;
void Game_first::update(float delta) {
    //��ʾ�������Ѫ��
    if (fireboy) {
        int blood_show = int(fireboy->blood_now / fireboy->blood * 100);
        if (blood_show < 0)blood_show = 0;
        std::string show = "Coin:" + std::to_string(fireboy->reward);
        show_reward->setString(show);
        store_message::coin = fireboy->reward;
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
        }
    }
    
    if(fireboy&& !End && !succeed){
        
        int minVal = 100;
        int maxVal = 800;
        int randomNum = minVal + (rand() % (maxVal - minVal + 1));
        if (fireboy) {
            //��ֹС�˿�bug����ȥ
            if (fireboy->sprite->getPositionY() < groundY) {
                fireboy->sprite->setPositionY(groundY);
            }
            if (fireboy->jump_max <4)
                temp++;
            if (temp == 90) {
                fireboy->jump_max +=1;
                temp = 0;
            }
            if (fireboy->jump_max < 2) {
                std::string show = "Jump too many times in a short period will make the character miss the runway,\n pressing the down arrow key to reset";
                show_warning = Label::createWithTTF(show, "fonts/Marker Felt.ttf", 55);
                show_warning->setPosition(Vec2(visibleSize.width/2 , visibleSize.height - 250));
                this->addChild(show_warning);
                // ����͸����Ϊ0��ʹ�ı���ȫ͸��
                show_warning->setOpacity(0);
                // �������䶯������͸����0���䵽255������ʱ��Ϊ1��
                auto fadeAction = FadeIn::create(1.0f);
                auto delay = DelayTime::create(2.0f);
                auto fadeout = FadeOut::create(1.0f);
              
                auto sequenceAction = Sequence::create(fadeAction, delay,fadeout, nullptr);
                // ������Ӧ����Label�ڵ�
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
            weapon_list.clear();
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
                if (i->sprite != nullptr)
                    weapon_list.push_back(i->sprite->getBoundingBox());
            }
            

            auto fire_b = fireboy->sprite->getBoundingBox();
            if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 850){
                for (int i=0;i<barrier_list.size();i++)
                    if (fire_b.intersectsRect(barrier_list[i]) && fireboy->sprite->getPositionX() < visibleSize.width + fireboy->sprite->getContentSize().width - 50) {
                        // ������������
                        // ���д������緢���¼���ִ��ĳЩ����
                        Vec2 position = Vec2(fireboy->sprite->getPosition().x + fireboy->sprite->getContentSize().width / 2.5f,
                            fireboy->sprite->getPosition().y);
                        auto boom= Boom(position);
                        this->addChild(boom);
                        //if(!barrier_list_origin[i]->interaction)
                        fireboy->blood_now -= 5;
                        /*barrier_list_origin[i]->interaction = true;*/
                        auto action = Blink::create(0.5, 3);      // ����һ��Blink����������2���ӣ���˸10��
                        auto callback = CallFunc::create([&]() {
                            show_blood->setVisible(true);        // ȷ����˸���������ǿɼ���
                            });
                        auto sequence = Sequence::create(action, callback, nullptr);   // ����һ��Sequence��������ִ��Blink��Ȼ��ִ��callback
                        show_blood->runAction(sequence);

                        barrier_list_origin[i]->sprite->setPositionX(2560 / 2 + 2560 + barrier_list_origin[i]->sprite->getPositionX() * 2);
                    }
            }

            for (int i = 0;i < coin_list.size();i++)
                if (fire_b.intersectsRect(coin_list[i]) && fireboy->sprite->getPositionX() < visibleSize.width + fireboy->sprite->getContentSize().width - 50) {
                    // ������������
                    // ���д������緢���¼���ִ��ĳЩ����
                    fireboy->reward++;
                    auto soundEffectID = AudioEngine::play2d("reward.mp3", false);
                    if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 550)
                        Coin_list[i]->sprite->setPosition(Vec2(visibleSize.width + Coin_list[i]->sprite->getContentSize().width, 200 + randomNum));
                    else
                        Coin_list[i]->sprite->setPositionX(-visibleSize.width - Coin_list[i]->sprite->getContentSize().width);
                    

                }
            for (int i = 0;i < weapon_list.size();i++) {
                for (int j = 0;j < barrier_list.size();j++) {
                    if (weapon_list[i].intersectsRect(barrier_list[j])) {
                        Vec2 position = Vec2(Weapon[i]->sprite->getPosition().x+ Weapon[i]->sprite->getContentSize().width/2,
                            Weapon[i]->sprite->getPosition().y);
                        auto boom2 = Boom(position);
                        this->addChild(boom2);
                        barrier_list_origin[j]->sprite->setPositionX(2560 / 2 + 2560 + barrier_list_origin[j]->sprite->getPositionX() * 2);
                        Weapon[i]->distroy_num--;
                        if (Weapon[i]->distroy_num == 0) {
                            this->removeChild(Weapon[i]->sprite);
                            for (int z=i;z < Weapon.size()-1;z++) {
                                Weapon[z] = Weapon[z + 1];
                            }
                            Weapon.pop_back();
                        }
                    }
                }
            }

            Size visibleSize = Director::getInstance()->getVisibleSize();
        }
        // �������������λ��
        background->setPosition(background->getPosition() + Vec2(velocity * delta, 0));
        Land->setPosition(Land->getPosition() + Vec2(velocity2 * delta, 0));
        Land2->setPosition(Land2->getPosition() + Vec2(velocity2 * delta, 0));
        if(fireboy)
            fireboy->sprite->setPosition(fireboy->sprite->getPosition() + Vec2(fireboy->velocity_player * delta * 2, 0));
        for (auto i : Weapon) {
            if (i->sprite->getPositionX() >= visibleSize.width + i->sprite->getContentSize().width) {
                this->removeChild(i->sprite);
                Weapon.pop_front();
            }
        }
        for (auto i : Weapon) {
            i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta * 2, 0));
        }
        if(background->getPositionX()<=3000){
            for (auto i : Barrier_list) {
                if (randomNum % i->rand_num == 0)
                    i->rand_barrier = true;
                if (i->rand_barrier)
                    i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta * 2, 0));
            }
        }
        if (background->getPositionX() <= 2000){
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
                i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta , 0));
        }
        for (auto i : Coin_list) {
                i->sprite->setPosition(i->sprite->getPosition() + Vec2(i->velocity * delta, 0));
        }
        if (background->getPositionX() + background->getContentSize().width / 2 <= visibleSize.width+10) {
            velocity=0,velocity2 = 0;
            fireboy->velocity_player = 200;
        }
        if (fireboy&&fireboy->sprite->getPositionX() > visibleSize.width + fireboy->sprite->getContentSize().width) {
            auto endgame = Label::createWithTTF("Successful!", "fonts/Marker Felt.ttf", 65);
            endgame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
            this->addChild(endgame, 0);
            // ����͸����Ϊ0��ʹ�ı���ȫ͸��
            endgame->setOpacity(0);
            // �������䶯������͸����0���䵽255������ʱ��Ϊ1��
            auto fadeAction = FadeIn::create(1.0f);
            // ������Ӧ����Label�ڵ�
            endgame->runAction(fadeAction);
            succeed = true;
        }

        if (Land->getPositionX() < -Land->getContentSize().width / 2) {
            Land->setPositionX(visibleSize.width + Land->getContentSize().width / 2 - 10);
        }
        if (Land2->getPositionX() < -Land->getContentSize().width / 2) {
            Land2->setPositionX(visibleSize.width + Land->getContentSize().width / 2 - 10);
        }
            
        if (background->getPositionX() + background->getContentSize().width / 2 >= visibleSize.width + 1050) {
            for (auto i : Barrier_NotMove_list) {
                if (i->sprite->getPositionX() < -Land->getContentSize().width/2) {
                    if (background->getPositionX() <= 3000 && replace_<Barrier_NotMove_list.size()) { //�滻�ϰ���Ϊ����
                        Sprite* temp = Sprite::create("jige.png");
                        temp->setPosition(Vec2(i->sprite->getPosition()));
                        temp->setScale(0.6f);
                        this->addChild(temp);
                        i->sprite = temp;
                        i->swing();
                        replace_ +=1;
                    }
                    i->sprite->setPositionX(visibleSize.width + Land->getContentSize().width / 2 + i->sprite->getPositionX());
                    i->interaction = false;
                    i->rand_barrier = false;
                }
            }
            for (auto i : Coin_list) {
                if (i->sprite->getPositionX() < -i->sprite->getContentSize().width) {
                    i->sprite->setPositionX(visibleSize.width + i->sprite->getContentSize().width);
                    i->rand_barrier = false;
                    i->interaction = false;
                }
            }
            for (auto i : Barrier_list) {
                if (i->sprite->getPositionX() < -i->sprite->getContentSize().width / 2) {
                    i->sprite->setPosition(Vec2(visibleSize.width + i->sprite->getContentSize().width / 2,50 + randomNum));
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
    }else if (End || succeed) {
        if(fireboy)store_message::coin = fireboy->reward;
        for (auto &i : Weapon) {
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
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
    if (pause == 180 ) {
        AudioEngine::stopAll();
        if(succeed){
            auto scene1 = game_first_second::createScene();
            Director::getInstance()->replaceScene(scene1);
        }else Director::getInstance()->pause();
    }
        
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Game_first::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Game_first::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}


void Game_first::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !End && !isKeyUpUp){
        if (!isKeyUp && fireboy->jump_max > 0){
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

    else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE  && !End && !isKeyUp){
        if (!isKeyUpUp&&fireboy->jump_max>0){
            isKeyUpUp = true;
            fireboy->BigJump(groundY);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !isKeyR && !End && fireboy->faster){
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
        isKeyR = true;
    }
    //else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !isKeyL)
    //{
    //    // �жϼ����Ҽ�ͷ���Ƿ��Ѱ���
    //    auto move_by = MoveBy::create(0.5, Vec2(-40, 0));
    //    auto sequenceAction = Sequence::create(move_by, nullptr);
    //    auto repeatAction = RepeatForever::create(sequenceAction);
    //    //// ���鿪ʼ�ܶ�����
    //    fireboy->runAction(repeatAction);
    //    move_L = repeatAction;
    //    isKeyL = true;
    //}
}

void Game_first::onDelayEnded(float dt) {
    isKeyUpUp = false;
}
// ����̧���¼��ص�����
void Game_first::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW){
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
        if (isKeyUp){
            isKeyUp = false;
        }
        if (isKeyUpUp){
            isKeyUpUp = false;
        }
    }
}
void Game_first::menuCloseCallback(Ref* pSender)
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
