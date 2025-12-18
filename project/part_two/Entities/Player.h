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
  int getGold() const;
  int getPotionCount() const;

  void addGold(int amount);
  void equipWeapon(const Item& weapon);
  void addPotion(const Item& potion);
  void usePotion();
  void displayInventory() const;
};

#endif