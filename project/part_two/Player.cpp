#include "Player.h"

#include <iostream>

#include "Enemy.h"

Player::Player(const std::string& n, int h, int a)
    : name(n), health(h), attack(a) {}

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}

void Player::attackEnemy(Enemy& enemy) {
  std::cout << name << " attacks for " << attack << " damage!\n";
  enemy.takeDamage(attack);
}

bool Player::isAlive() const { return health > 0; }

std::string Player::getName() const { return name; }

int Player::getHealth() const { return health; }

int Player::getAttack() const { return attack; }