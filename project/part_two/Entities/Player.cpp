#include "Player.h"

#include <iostream>

#include "../Systems/Shop.H"
#include "Enemy.h"

Player::Player(const std::string& n, int h, int a)
    : name(n),
      health(h),
      maxHealth(h),
      baseAttack(a),
      gold(0),
      equippedWeapon(nullptr),
      potionCount(0) {}

Player::~Player() { delete equippedWeapon; }

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}

void Player::heal(int amount) {
  health += amount;
  if (health > maxHealth) health = maxHealth;
  std::cout << name << " HP: " << health << "/" << maxHealth << "\n";
}

void Player::attackEnemy(Enemy& enemy) {
  int totalAttack = getAttack();
  std::cout << name << " attacks for " << totalAttack << " damage!\n";
  enemy.takeDamage(totalAttack);
}

bool Player::isAlive() const { return health > 0; }

std::string Player::getName() const { return name; }

int Player::getHealth() const { return health; }

int Player::getMaxHealth() const { return maxHealth; }

int Player::getAttack() const {
  int totalAttack = baseAttack;
  if (equippedWeapon != nullptr) {
    totalAttack += equippedWeapon->statBonus;
  }
  return totalAttack;
}

int Player::getGold() const { return gold; }

int Player::getPotionCount() const { return potionCount; }

void Player::addGold(int amount) {
  gold += amount;
  if (amount > 0) {
    std::cout << "You received " << amount << " gold! Total: " << gold << "\n";
  }
}

void Player::equipWeapon(const Item& weapon) {
  if (equippedWeapon != nullptr) {
    std::cout << "Unequipped: " << equippedWeapon->name << "\n";
    inventory.push_back(*equippedWeapon);
    delete equippedWeapon;
  }

  equippedWeapon = new Item(weapon);
  std::cout << "Equipped: " << weapon.name << " (+" << weapon.statBonus
            << " attack)\n";
  std::cout << "Total attack: " << getAttack() << "\n";
}

void Player::addPotion(const Item& potion) {
  potionCount++;
  std::cout << "Added " << potion.name << " to inventory!\n";
  std::cout << "Total potions: " << potionCount << "\n";
}

void Player::usePotion() {
  if (potionCount > 0) {
    heal(30);
    potionCount--;
    std::cout << "You used a potion and restored 30 HP!\n";
    std::cout << "Potions remaining: " << potionCount << "\n";
  } else {
    std::cout << "You don't have any potions!\n";
  }
}

void Player::displayInventory() const {
  std::cout << "\n=== INVENTORY ===\n";
  std::cout << "Gold: " << gold << "\n";
  std::cout << "Potions: " << potionCount << "\n\n";

  std::cout << "Equipped Weapon: ";
  if (equippedWeapon != nullptr) {
    std::cout << equippedWeapon->name << " (+" << equippedWeapon->statBonus
              << " attack)\n";
  } else {
    std::cout << "None (Bare hands)\n";
  }

  std::cout << "\nTotal Attack: " << getAttack() << "\n";

  if (!inventory.empty()) {
    std::cout << "\nStored Weapons:\n";
    for (const auto& item : inventory) {
      std::cout << "- " << item.name << " (+" << item.statBonus << " attack)\n";
    }
  }
}