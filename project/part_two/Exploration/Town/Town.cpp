#include "Town.h"

#include <iostream>
#include <limits>

#include "../../Systems/Shop.H"

using namespace std;

int getTownChoice(int min, int max) {
  int choice;
  while (true) {
    cout << "Enter your choice: ";
    if (cin >> choice && choice >= min && choice <= max) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return choice;
    } else {
      cout << "Invalid choice! Try again.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void visitQuestBoard(QuestManager& questManager) {
  cout << "\n=== QUEST BOARD ===\n";
  cout << "You approach the wooden quest board in the town square.\n";
  cout << "Several notices are pinned to it.\n\n";

  cout << "Available Quests:\n";
  cout << "1. [Goblin Slayer] - Defeat 3 goblins (Reward: 50 gold)\n";
  cout << "2. [Forest Patrol] - Defeat 5 goblins (Reward: 100 gold)\n";
  cout << "3. [Goblin Chief] - Defeat 10 goblins (Reward: 200 gold)\n";
  cout << "4. Leave quest board\n\n";

  int choice = getTownChoice(1, 4);

  if (choice == 1) {
    Quest quest("Goblin Slayer", "Defeat 3 goblins in the forest", 3, 50);
    questManager.addQuest(quest);
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 2) {
    Quest quest("Forest Patrol", "Defeat 5 goblins in the forest", 5, 100);
    questManager.addQuest(quest);
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 3) {
    Quest quest("Goblin Chief", "Defeat 10 goblins - prove your worth!", 10,
                200);
    questManager.addQuest(quest);
    cout << "\nPress Enter to continue...";
    cin.get();
  } else {
    cout << "\nYou step away from the quest board.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  }
}

void visitBlacksmith(Player& player) {
  Shop blacksmith("Blacksmith's Forge");

  Item ironSword = {"Iron Sword", "A sturdy iron blade (+10 attack)", 75,
                    "weapon", 10};
  Item steelSword = {"Steel Sword", "A well-crafted steel weapon (+20 attack)",
                     150, "weapon", 20};
  Item masterSword = {"Master Sword", "A legendary blade (+35 attack)", 300,
                      "weapon", 35};

  blacksmith.addShopItem(ironSword);
  blacksmith.addShopItem(steelSword);
  blacksmith.addShopItem(masterSword);

  while (true) {
    cout << "\nThe blacksmith greets you warmly.\n";
    cout << "\"Looking for quality weapons? Take a look!\"\n";
    cout << "Your gold: " << player.getGold()
         << " | Current attack: " << player.getAttack() << "\n";

    blacksmith.displayShop();

    int choice = getTownChoice(1, 4);

    if (choice == 4) {
      cout << "\n\"Come back anytime!\"\n";
      cout << "\nPress Enter to continue...";
      cin.get();
      break;
    } else {
      blacksmith.purchaseItem(player, choice);
      cout << "\nPress Enter to continue...";
      cin.get();
    }
  }
}

void visitTavern(Player& player) {
  Shop tavern("The Rusty Mug Tavern");

  Item healthPotion = {"Health Potion", "Restores 30 HP", 20, "potion", 30};

  tavern.addShopItem(healthPotion);

  while (true) {
    cout << "\nYou enter the cozy tavern.\n";
    cout << "The bartender wipes down the bar and smiles.\n";
    cout << "\"What can I get you?\"\n";
    cout << "Your gold: " << player.getGold()
         << " | Potions: " << player.getPotionCount() << "\n";

    tavern.displayShop();

    int choice = getTownChoice(1, 2);

    if (choice == 2) {
      cout << "\n\"Safe travels, friend!\"\n";
      cout << "\nPress Enter to continue...";
      cin.get();
      break;
    } else {
      tavern.purchaseItem(player, choice);
      cout << "\nPress Enter to continue...";
      cin.get();
    }
  }
}

void exploreTown(Player& player, QuestManager& questManager) {
  cout << "\n=== TOWN ===\n";
  cout << "You walk through the peaceful town square.\n";
  cout << "Merchants are selling their wares and children are playing.\n";
  cout << "A wooden quest board stands prominently in the center.\n\n";

  cout << "Where do you want to go?\n";
  cout << "1. Visit the quest board\n";
  cout << "2. Visit the blacksmith\n";
  cout << "3. Go to the tavern\n";
  cout << "4. Turn in completed quests\n";
  cout << "5. View inventory\n";
  cout << "6. Leave town\n\n";

  int choice = getTownChoice(1, 6);

  if (choice == 1) {
    visitQuestBoard(questManager);
  } else if (choice == 2) {
    visitBlacksmith(player);
  } else if (choice == 3) {
    visitTavern(player);
  } else if (choice == 4) {
    questManager.checkAndCompleteQuests(player);
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 5) {
    player.displayInventory();
    cout << "\nPress Enter to continue...";
    cin.get();
  } else {
    cout << "\nYou leave the safety of the town.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  }
}