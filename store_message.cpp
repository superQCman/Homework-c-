#include "store_message.h"
int store_message::coin = 0;
string store_message::player = "run2-1(1).png";
string store_message::background = "background_game.png";
string store_message::wepon_first = "pencil1.png";
string store_message::wepon_second =  "eraser.png";
int store_message::DegreeOfDif = 2;
int store_message::paidPlayer[3] = { 0, 0, 0 };
int store_message::paidWeapon[4] = { 0, 0, 0,0 };
int store_message::choosePlayer[3] = { 0, 0, 0 };
int store_message::chooseWeapon[4] = { 0, 0, 0,0 };
std::string store_message::PlayerNames[3] = { "run2-1(1).png","fox2-1(1).png","rat2-1(1).png" };
std::string store_message::WeaponNames[4] = { "eraser.png","FlashLight.png","pencil1.png","FireBall.png" };
int store_message::WeaponPower[4] = { 1,2,2,4 };
std::string store_message::StoreList[4] = { "intro_Lightning Nick.png", "intro_chinchilla.png", "intro_Aegis.png", "intro_fireball.png" };