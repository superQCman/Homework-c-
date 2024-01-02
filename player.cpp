#include "player.h"
#include "cocos2d.h"
#include"Scene_one.h"
#include"store_message.h"
#include<deque>
#include<vector>
using namespace cocos2d;

//��ʼ������
Base_player::Base_player(double groundy,std::string first_pic,std::string second_first,std::string second_second,int pic_num,int position) {
    sprite = Sprite::create(first_pic);
    if (sprite == nullptr) {
        CCLOG("problem loading 'run-1.png'");
    }
    else {
        // Position the sprite at the center of the screen
        if(position==1)sprite->setPosition(Vec2(sprite->getContentSize().width * 2, groundy));
        else if(position==2)sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - sprite->getContentSize().width * 1.5, groundy+50));
        // Add the sprite as a child to this layer

        // Add frames to the vector
        for (int i = 1; i <= pic_num; i++) {
            SpriteFrame* frame=NULL;
            if (position == 1) frame = SpriteFrame::create(second_first + std::to_string(i) + second_second, Rect(0, 0, 300, 200)); // Set width and height here
            else if (position == 2) frame = SpriteFrame::create(second_first + std::to_string(i) + second_second, Rect(0, 0, 300, 260)); // Set width and height here
            frames.pushBack(frame);
        }
        
        // Create the animation out of the frames
        if (position == 1)animation = Animation::createWithSpriteFrames(frames, 0.05f);
        else if (position == 2)animation = Animation::createWithSpriteFrames(frames, 0.1f);
        // Create an animate action from the animation
        animate = Animate::create(animation);
        // Run it and repeat it forever
        //sprite->runAction(RepeatForever::create(animate));
    }
 
}
//��ȡ�������ʱ��
int& Base_player::get_accuracy_time() {
    return accuracy_time;
}
//��ȡ���������ָ�ʱ��
int& Base_player::get_sleep_time() {
    return sleep_time;
}

int& Base_player::get_small_sleep_time() {
    return small_sleep_time;
}
//����Fireboy�ļ���ʱ��
void Fireboy::set_accuracy_time() {
    get_accuracy_time() = 180;
}
//����Fireboy�������ָ�ʱ��
void Fireboy::set_sleep_time() {
    get_sleep_time() = 900;
    energy=full_energy = 100;
}

void Fireboy::set_small_sleep_time() {
    get_small_sleep_time() = 900;
}

//����Fireboy��������
void Fireboy::BigJump(double groundY) {
    jump_max--;
    auto move_by = JumpBy::create(1, Vec2(0, 1), 500, 1);
    auto delay = DelayTime::create(1.0f);
    auto reset = MoveTo::create(0, Vec2(this->sprite->getPositionX(), groundY));
    auto sequenceAction_up = Sequence::create(move_by, delay, nullptr);
    sequence = sequenceAction_up;
    this->sprite->runAction(sequenceAction_up);
}
void Fireboy::Jump(double groundY) {
    jump_max--;
    auto move_by = JumpBy::create(0.8, Vec2(0, 1), 300, 1);
    auto delay = DelayTime::create(0.5f);
    auto sequenceAction_up = Sequence::create(move_by, delay, nullptr);
    sequence = sequenceAction_up;
    this->sprite->runAction(sequenceAction_up);
}
//void Fireboy::run() {
//    // Create a vector to hold sprite frames
//    Vector<SpriteFrame*> frames;
//
//    // Add frames to the vector
//    for (int i = 1; i <= 8; i++) {
//        auto frame = SpriteFrame::create("run2-" + std::to_string(i) + "(1).png", Rect(0, 0, 300, 200)); // Set width and height here
//        frames.pushBack(frame);
//    }
//
//    // Create the animation out of the frames
//    Animation* animation = Animation::createWithSpriteFrames(frames, 0.05f);
//
//    // Create an animate action from the animation
//    Animate* animate = Animate::create(animation);
//
//    // Run it and repeat it forever
//    this->sprite->runAction(Repeat::create(animate, 3));
//
//}

//����Fireboy�ƶ�����
void Fireboy::Move(double groundY) {
    if (sequence != NULL && this->sprite->getPosition().y>groundY+5) {
        this->sprite->stopAction(sequence);
        auto move = MoveTo::create(0.2f, Vec2(this->sprite->getPositionX(), groundY));
        auto delay = DelayTime::create(0.5f);
        auto sequenceAction_up = Sequence::create(move, delay, nullptr);
        this->sprite->runAction(sequenceAction_up);
    }
}

//����FireboyѪ��
void Fireboy::set_blood() {
    this->blood = 20.0;
    this->blood_now = 20.0;
}

//����TeacherѪ��
void Teacher::set_blood() {
    this->blood = 80.0;
    this->blood_now = 80.0;
}

//����Fireboy��������
void Fireboy::throw_weapon(Base_player *fireboy, std::string pic,Barrier_base* newSprite) {
    newSprite->set_velocity(100);
    if (newSprite->sprite != nullptr) {
        newSprite->sprite->setPosition(Vec2(fireboy->sprite->getPositionX() + 20, fireboy->sprite->getPositionY()));
        // Ҳ����Ӷ���������µľ���
        float duration = 0.5f;  // ��תһ�������ʱ��
        auto rotateAction = RotateBy::create(duration, 360);

        // ��������ѭ������
        auto repeatAction = RepeatForever::create(rotateAction);

        // Ӧ�ö���������
        newSprite->sprite->runAction(repeatAction);
    }
}

//����Teacher��������
void Teacher::throw_weapon(Base_player* boss, std::string, Barrier_base* newSprite) {
    newSprite->set_velocity(-300);
    newSprite->sprite->setPosition(Vec2(boss->sprite->getPositionX() - 20, boss->sprite->getPositionY()));
    
}

