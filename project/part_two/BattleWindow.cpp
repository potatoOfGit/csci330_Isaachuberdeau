#include <iostream>
#include <limits>

#include "Entities/Player.h"
#include "Exploration/Forest/Forest.h"
#include "Exploration/Town/Town.h"
#include "Systems/Quest.h"

using namespace std;

int getMainChoice(int min, int max) {
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

int main() {
  cout << "=================================\n";
  cout << "     ADVENTURE GAME\n";
  cout << "=================================\n\n";

  string playerName;
  cout << "Enter your hero's name: ";
  getline(cin, playerName);

  Player hero(playerName, 100, 25);
  QuestManager questManager;

  cout << "\nWelcome, " << hero.getName() << "!\n";
  cout << "Your adventure begins...\n";
  cout << "\nPress Enter to continue...";
  cin.get();

  bool playing = true;

  while (playing && hero.isAlive()) {
    cout << "\n=== MAIN MENU ===\n";
    cout << "HP: " << hero.getHealth() << "/" << hero.getMaxHealth()
         << " | Attack: " << hero.getAttack() << " | Gold: " << hero.getGold()
         << " | Potions: " << hero.getPotionCount() << "\n\n";
    cout << "Where do you want to go?\n";
    cout << "1. Explore the town\n";
    cout << "2. Venture into the forest\n";
    cout << "3. View quests\n";
    cout << "4. View inventory\n";
    cout << "5. Rest (end game)\n\n";

    int choice = getMainChoice(1, 5);

    if (choice == 1) {
      exploreTown(hero, questManager);
    } else if (choice == 2) {
      exploreForest(hero, questManager);
    } else if (choice == 3) {
      questManager.displayActiveQuests();
      questManager.displayCompletedQuests();
      cout << "\nPress Enter to continue...";
      cin.get();
    } else if (choice == 4) {
      hero.displayInventory();
      cout << "\nPress Enter to continue...";
      cin.get();
    } else {
      cout << "\nYou decide to rest for the day.\n";
      cout << "Your adventure ends here... for now.\n";
      playing = false;
    }
  }

  if (!hero.isAlive()) {
    cout << "\n=================================\n";
    cout << "      GAME OVER\n";
    cout << "=================================\n";
  } else {
    cout << "\nThanks for playing!\n";
  }

  return 0;
}