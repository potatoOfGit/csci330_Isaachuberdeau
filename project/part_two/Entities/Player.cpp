#include "Player.h"

#include <cmath>
#include <iostream>

#include "../Systems/Shop.H"
#include "Enemy.h"

Player::Player(const std::string& n, int h, int a)
    : name(n),
      health(h),
      maxHealth(h),
      baseAttack(a),
      defense(5),
      level(1),
      experience(0),
      experienceToNextLevel(100),
      gold(0),
      equippedWeapon(nullptr),
      potionCount(0) {}

Player::~Player() { delete equippedWeapon; }

void Player::takeDamage(int damage) {
  int reducedDamage = calculateDamageReduction(damage);
  health -= reducedDamage;
  if (health < 0) health = 0;

  std::cout << name << " took " << reducedDamage << " damage";
  if (reducedDamage < damage) {
    std::cout << " (blocked " << (damage - reducedDamage) << ")";
  }
  std::cout << "!\n";
}

void Player::heal(int amount) {
  health += amount;
  if (health > maxHealth) health = maxHealth;
  std::cout << name << " HP: " << health << "/" << maxHealth << "\n";
}

void Player::attackEnemy(Enemy& enemy) {
  int totalDamage = calculateDamage(getAttack());
  std::cout << name << " attacks for " << totalDamage << " damage!\n";
  enemy.takeDamage(totalDamage);
}

bool Player::isAlive() const { return health > 0; }

std::string Player::getName() const { return name; }

int Player::getHealth() const { return health; }

int Player::getMaxHealth() const { return maxHealth; }

int Player::getAttack() const {
  int totalAttack = baseAttack + (level * 2);
  if (equippedWeapon != nullptr) {
    totalAttack += equippedWeapon->statBonus;
  }
  return totalAttack;
}

int Player::getDefense() const { return defense + level; }

int Player::getLevel() const { return level; }

int Player::getExperience() const { return experience; }

int Player::getExperienceToNextLevel() const { return experienceToNextLevel; }

int Player::getGold() const { return gold; }

int Player::getPotionCount() const { return potionCount; }

void Player::addGold(int amount) {
  gold += amount;
  if (amount > 0) {
    std::cout << "You received " << amount << " gold! Total: " << gold << "\n";
  }
}

void Player::addExperience(int xp) {
  experience += xp;
  std::cout << "+" << xp << " XP! (" << experience << "/"
            << experienceToNextLevel << ")\n";

  while (experience >= experienceToNextLevel) {
    levelUp();
  }
}

void Player::levelUp() {
  level++;
  experience -= experienceToNextLevel;
  experienceToNextLevel = static_cast<int>(100 * std::pow(1.5, level - 1));

  int healthIncrease = 20;
  int attackIncrease = 3;
  int defenseIncrease = 2;

  maxHealth += healthIncrease;
  health = maxHealth;
  baseAttack += attackIncrease;
  defense += defenseIncrease;

  std::cout << "\n*** LEVEL UP! ***\n";
  std::cout << "You are now level " << level << "!\n";
  std::cout << "Max HP +" << healthIncrease << " (" << maxHealth << ")\n";
  std::cout << "Attack +" << attackIncrease << " (" << getAttack() << ")\n";
  std::cout << "Defense +" << defenseIncrease << " (" << getDefense() << ")\n";
  std::cout << "HP fully restored!\n";
}

int Player::calculateDamage(int baseDamage) const {
  int variance = (rand() % 5) - 2;
  return baseDamage + variance;
}

int Player::calculateDamageReduction(int incomingDamage) const {
  int reduction = getDefense() / 2;
  int finalDamage = incomingDamage - reduction;
  return (finalDamage > 0) ? finalDamage : 1;
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

void Player::displayStats() const {
  std::cout << "\n=== " << name << " - Level " << level << " ===\n";
  std::cout << "HP: " << health << "/" << maxHealth << "\n";
  std::cout << "Attack: " << getAttack() << " (Base: " << baseAttack << ")\n";
  std::cout << "Defense: " << getDefense() << "\n";
  std::cout << "XP: " << experience << "/" << experienceToNextLevel << "\n";
  std::cout << "Gold: " << gold << "\n";
}