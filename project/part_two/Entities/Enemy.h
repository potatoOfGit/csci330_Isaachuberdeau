#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Player;

class Enemy {
 private:
  std::string name;
  int health;
  int attack;
  int xpReward;

 public:
  Enemy(const std::string& n, int h, int a, int xp);
  void takeDamage(int damage);
  void attackPlayer(Player& player);
  bool isAlive() const;
  std::string getName() const;
  int getHealth() const;
  int getAttack() const;
  int getXPReward() const;
};

#endif