#pragma once
#include<string>
#include<vector>
using namespace std;
class store_message{
public:
	static int coin;
	static string player;
	static string background;
	static string wepon_first;
	static string wepon_second;
	static int DegreeOfDif;
	static int paidPlayer[3];
	static int paidWeapon[4];
	static int choosePlayer[3];
	static int chooseWeapon[4];
	static std::string PlayerNames[3];
	static std::string WeaponNames[4];
	static int WeaponPower[4];
	static std::string StoreList[4];
};

