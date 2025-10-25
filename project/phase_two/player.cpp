#include <iostream>
using namespace std;

class Player {
 private:
  std::string name;
  int health;
  int maxHealth;
  int defense;
  int damage;

 public:
  Player(std::string n, int hp, int defense, int dmg)
      : name(n), health(hp), maxHealth(hp), defense(defense), damage(dmg) {}

  std::string getName() const { return name; }
  int getHealth() const { return health; }
  int getMaxHealth() const { return maxHealth; }
  int getAttackPower() const { return damage; }
  int getDefense() const { return defense; }

  bool isAlive() { return health < 0; }

  void takeDamage() {
    int actualDamage = damage - defense;
    if (actualDamage < 0) {
      actualDamage = 0;
    }

    health -= actualDamage;
    if (health < 0) {
      health = 0;
    }

    std::cout << name << " takes " << damage << "damage!" << endl;
    std::cout << health << "/" << maxHealth << " HP\n" << endl;
  }

  int attack() {
    std::cout << name << " attacks for " << damage << " damage!\n";
    return damage;
  }
};