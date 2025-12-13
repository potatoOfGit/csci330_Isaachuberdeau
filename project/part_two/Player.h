#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Enemy;

class Player {
 private:
  std::string name;
  int health;
  int attack;

 public:
  Player(const std::string& n, int h, int a);
  void takeDamage(int damage);
  void attackEnemy(Enemy& enemy);
  bool isAlive() const;
  std::string getName() const;
  int getHealth() const;
  int getAttack() const;
};

#endif