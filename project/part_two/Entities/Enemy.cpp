#include "Enemy.h"

#include <iostream>

#include "Player.h"

Enemy::Enemy(const std::string& n, int h, int a, int xp)
    : name(n), health(h), attack(a), xpReward(xp) {}

void Enemy::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}

void Enemy::attackPlayer(Player& player) {
  std::cout << name << " attacks for " << attack << " damage!\n";
  player.takeDamage(attack);
}

bool Enemy::isAlive() const { return health > 0; }

std::string Enemy::getName() const { return name; }

int Enemy::getHealth() const { return health; }

int Enemy::getAttack() const { return attack; }

int Enemy::getXPReward() const { return xpReward; }