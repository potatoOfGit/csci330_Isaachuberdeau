#include "Shop.H"

#include <iostream>

#include "../Entities/Player.h"

using namespace std;

Shop::Shop(const string& name) : shopName(name) {}

void Shop::addShopItem(const Item& item) { shopItems.push_back(item); }

void Shop::displayShop() const {
  cout << "\n=== " << shopName << " ===\n";
  cout << "Available items:\n\n";

  for (size_t i = 0; i < shopItems.size(); i++) {
    cout << (i + 1) << ". " << shopItems[i].name << " - " << shopItems[i].price
         << " gold\n";
    cout << "   " << shopItems[i].description << "\n\n";
  }

  cout << (shopItems.size() + 1) << ". Leave shop\n";
}

bool Shop::purchaseItem(Player& player, int choice) {
  if (choice < 1 || choice > shopItems.size()) {
    return false;
  }

  const Item& item = shopItems[choice - 1];

  if (player.getGold() >= item.price) {
    player.addGold(-item.price);

    if (item.type == "weapon") {
      player.equipWeapon(item);
    } else if (item.type == "potion") {
      player.addPotion(item);
    }

    cout << "\nPurchase successful!\n";
    return true;
  } else {
    cout << "\nNot enough gold! You need " << item.price
         << " gold but only have " << player.getGold() << ".\n";
    return false;
  }
}