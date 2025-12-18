#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <vector>

class Player;

struct Item {
  std::string name;
  std::string description;
  int price;
  std::string type;
  int statBonus;
};

class Shop {
 private:
  std::vector<Item> shopItems;
  std::string shopName;

 public:
  Shop(const std::string& name);
  void addShopItem(const Item& item);
  void displayShop() const;
  bool purchaseItem(Player& player, int choice);
};

#endif