#include "Character.h"
#include "MonsterFabric.h"
#include <iostream>

Character::~Character() {
	delete damage;
	delete hp;
}

bool Character::isAlive() {
	if (*this->hp > 0)
		return true;
	else
		return false;
}

double Character::getHP() {
	return *hp;
}

void Character::setHP(double* hp) {
	this->hp = new double(*hp);
}

Hero::Hero(const char* name, int level) {
	this->name = name;
	this->level = level;
	this->hp = new double(level * 10.0);
	this->damage = new double(level * 1.50);
}

Hero::Hero(const char* name, int level, Weapon weapon) {
	this->isWeapon = true;
	this->name = name;
	this->level = level;
	this->hp = new double(level * 10.0);
	this->damage = new double(level * 1.50 + weapon.getDamage());
}

void Hero::attack(Character& monster) {
	if (isAlive()) {
		if (monster.isAlive()) {
			monster.setHP(new double(monster.getHP() - *damage));
			if (monster.getHP() < 0) monster.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << ". Monster HP: " << monster.getHP() << ".\n";
		}
		else
			std::cout << "Monster is dead.\n\n";
	}
}


void Hero::displayHero() {
	std::cout << "-Hero info-\n";
	std::cout << "Name : " << this->name << ".\n";
	std::cout << "Level: " << this->level << ".\n";
	std::cout << "HP   : " << *this->hp << ".\n";
	if(this->isWeapon == false) 
		std::cout << "Base damage: "    << *this->damage << ".\n";
	else 
		std::cout << "Summary damage: " << *this->damage << ".\n\n";
}

MonsterA::MonsterA(const char* name, int level) {
	this->name = name;
	this->level = level;
	this->damage = new double(level * 1.5);
	this->hp = new double(level * 8);
}

void Monster::setDamage(double* damage) {
	this->damage = new double(*damage);
}

void MonsterA::attack(Character& hero) {
	if (isAlive()) {
		if (hero.isAlive() && this->getHP() > 10) {
			hero.setHP(new double(hero.getHP() - *damage));
			if (hero.getHP() < 0) hero.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << ". Hero HP: " << hero.getHP() << ".\n";
		}
		else if (hero.isAlive() && this->getHP() <= 10) {
			setDamage(new double(*damage * 2));
			hero.setHP(new double(hero.getHP() - *damage));
			if (hero.getHP() < 0) hero.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << ". Hero HP: " << hero.getHP() << ".\n";
		}
		else if (!hero.isAlive())
			std::cout << hero.name << " is dead.\n\n";
	}
}

void Monster::displayMonster() {
	std::cout << "-Monster info-\n";
	std::cout << "Name  : " << this->name << ".\n";
	std::cout << "Level : " << this->level << ".\n";
	std::cout << "HP    : " << this->getHP() << ".\n";
	std::cout << "Damage: " << *this->damage << ".\n\n";
}

MonsterB::MonsterB(const char* name, int level) {
	this->name = name;
	this->level = level;
	this->damage = new double(level * 1.5);
	this->hp = new double(level * 8);
}

void MonsterB::attack(Character& hero) {
	if (isAlive()) {
		unsigned int rng = rand() % 2;
		if (hero.isAlive() && rng == 0) {
			hero.setHP(new double(hero.getHP() - *damage));
			if (hero.getHP() < 0) hero.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << ". Hero HP: " << hero.getHP() << ".\n";
		}
		else if (hero.isAlive() && rng == 1) {
			//setDamage(new double(*damage * 2));
			hero.setHP(new double(hero.getHP() - *damage * 2));
			if (hero.getHP() < 0) hero.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << "(2x). Hero HP: " << hero.getHP() << ".\n";
		}
		else if (!hero.isAlive())
			std::cout << hero.name << " is dead.\n\n";
	}
}

MonsterC::MonsterC(const char* name, int level) {
	this->isReadyToAttack = true;
	this->name = name;
	this->level = level;
	this->damage = new double(level * 3);
	this->hp = new double(level * 8);
}

void MonsterC::setAttackFlag(bool flag) {
	isReadyToAttack = flag;
}

bool MonsterC::getAttackFlag() {
	return this->isReadyToAttack;
}

void MonsterC::attack(Character& hero) {
	if (isAlive()) {
		if (hero.isAlive() && getAttackFlag()) {
			hero.setHP(new double(hero.getHP() - *damage * 3));
			if (hero.getHP() < 0) hero.setHP(new double(0));
			std::cout << this->name << " dealt " << *this->damage << "(3x). Hero HP: " << hero.getHP() << ".\n";
			this->setAttackFlag(false);
		}
		else if (hero.isAlive() && !getAttackFlag()) {
			std::cout << this->name << " is waiting...\n";
			this->setAttackFlag(true);
		}
		else if (!hero.isAlive()) {
			std::cout << hero.name << " is dead.\n\n";
		}
	}
}

int main() {

	Weapon sword("Excalibur", 5); 
	Hero saber("Arturia", 5, sword);
	saber.displayHero();
	std::cout << "\n";
	sword.displayWeapon();

	MonsterFabric *fabric;
	int levelChoosen = 0;
	std::cout << "Enter the level: ";
	while(levelChoosen < 1 || levelChoosen > 2) std::cin >> levelChoosen;
	
	Monster *slime;

	if (levelChoosen == 1) {
		fabric = new LevelEasy();
		slime = fabric->createMonster();
	} 
	else {
		fabric = new LevelHard();
		slime = fabric->createMonster();
	}

	while (saber.isAlive() && slime->isAlive()) {
		saber.attack(*slime);
		if (!slime->isAlive()) {
			std::cout << slime->name << " is dead.\n\n";
			saber.displayHero();
			exit;
		}
		slime->attack(saber);
		if (!saber.isAlive()) {
			std::cout << saber.name << " is dead.\n\n";
			slime->displayMonster();
			exit;
		}
	}

	system("pause");
	return 0;
}