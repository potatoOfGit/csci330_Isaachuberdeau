#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Enemy;
struct Item;

class Player {
 private:
  std::string name;
  int health;
  int maxHealth;
  int baseAttack;
  int defense;
  int level;
  int experience;
  int experienceToNextLevel;
  int gold;
  std::vector<Item> inventory;
  Item* equippedWeapon;
  int potionCount;

 public:
  Player(const std::string& n, int h, int a);
  ~Player();

  void takeDamage(int damage);
  void heal(int amount);
  void attackEnemy(Enemy& enemy);
  bool isAlive() const;

  std::string getName() const;
  int getHealth() const;
  int getMaxHealth() const;
  int getAttack() const;
  int getDefense() const;
  int getLevel() const;
  int getExperience() const;
  int getExperienceToNextLevel() const;
  int getGold() const;
  int getPotionCount() const;

  void addGold(int amount);
  void addExperience(int xp);
  void equipWeapon(const Item& weapon);
  void addPotion(const Item& potion);
  void usePotion();
  void displayInventory() const;
  void displayStats() const;

 private:
  void levelUp();
  int calculateDamage(int baseDamage) const;
  int calculateDamageReduction(int incomingDamage) const;
};

#endif