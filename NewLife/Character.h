#pragma once
#include "Weapon.h"

class Character {
public:
	double* hp;
	double* damage;
	int level;
	const char* name;

	bool isAlive();
	double getHP();
	void setHP(double* hp);

	virtual void attack(Character& hero) = 0;

	~Character();
};

class Hero : public Character {
private:
	Weapon weapon;
	bool isWeapon = false;
public:
	Hero(const char* name, int level);
	Hero(const char* name, int level, Weapon weapon);

	void attack(Character &monster);
	void displayHero();
};

class Monster : public Character {
public:
	void setDamage(double* damage);
	void displayMonster();
};

class MonsterA : public Monster {
public:
	MonsterA(const char* name, int level);
	void attack(Character &hero);
};

class MonsterB : public Monster {
public:
	MonsterB(const char* name, int level);
	void attack(Character& hero);
};

class MonsterC : public Monster {
private:
	bool isReadyToAttack;
public:
	MonsterC(const char* name, int level);
	void attack(Character& hero);
	
	bool getAttackFlag();
	void setAttackFlag(bool flag);
};

