#include <iostream>
using namespace std;

class Enemy {
 private:
  std::string name;
  int health;
  int maxHealth;
  int attackPower;
  int defense;
  int experience;

 public:
  Enemy(std::string n, int hp, int atk, int def, int exp)
      : name(n),
        health(hp),
        maxHealth(hp),
        attackPower(atk),
        defense(def),
        experience(exp) {}

  std::string getName() const { return name; }
  int getHealth() const { return health; }
  int getMaxHealth() const { return maxHealth; }
  int getAttackPower() const { return attackPower; }
  int getDefense() const { return defense; }
  int getExperience() const { return experience; }

  bool isAlive() const { return health > 0; }

  void takeDamage(int damage) {
    int actualDamage = damage - defense;
    if (actualDamage < 0) {
      damage = 0;
    }

    health -= actualDamage;
    if (health < 0) {
      health = 0;
    }

    std::cout << name << " takes " << damage << "damage!" << endl;
    std::cout << health << "/" << maxHealth << " HP\n" << endl;
  }

  int attack() {
    std::cout << name << " attacks for " << attackPower << " damage!\n";
    return attackPower;
  }

  void displayStatus() const {
    std::cout << name << " - HP: " << health << "/" << maxHealth << "\n";
  }
};