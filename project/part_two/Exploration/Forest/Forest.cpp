#include "Forest.h"

#include <iostream>
#include <limits>

#include "../../Entities/Enemy.h"
#include "../../Systems/Combat.h"

using namespace std;

int getForestChoice(int min, int max) {
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

void exploreForest(Player& player, QuestManager& questManager) {
  cout << "\n=== DARK FOREST ===\n";
  cout << "You venture into the mysterious forest.\n";
  cout << "The trees loom overhead, blocking out the sunlight.\n\n";

  cout << "What do you do?\n";
  cout << "1. Follow the path deeper\n";
  cout << "2. Search the bushes\n";
  cout << "3. Use a potion (Potions: " << player.getPotionCount() << ")\n";
  cout << "4. Return to safety\n\n";

  int choice = getForestChoice(1, 4);

  if (choice == 1) {
    cout << "\nYou walk deeper into the forest...\n";
    cout << "Suddenly, you hear a growl!\n";
    cout << "A wild goblin appears!\n";
    cout << "\nPress Enter to continue...";
    cin.get();

    Enemy goblin("Goblin", 50, 15);
    startBattle(player, goblin);

    if (player.isAlive() && !goblin.isAlive()) {
      cout << "\nYou defeated the goblin!\n";
      questManager.updateQuestProgress("Goblin");
    }

  } else if (choice == 2) {
    cout << "\nYou search through the bushes...\n";
    cout << "You find some herbs! (But you can't use them yet)\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 3) {
    player.usePotion();
    cout << "\nPress Enter to continue...";
    cin.get();
  } else {
    cout << "\nYou carefully make your way back.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  }
}