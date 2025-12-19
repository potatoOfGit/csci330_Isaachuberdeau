#include "GameManager.h"

#include <iostream>
#include <limits>

#include "Exploration/Forest/Forest.h"
#include "Exploration/Town/Town.h"
#include "Systems/InputUtils.h"

using namespace std;

GameManager::GameManager()
    : player(nullptr), questManager(nullptr), isRunning(true) {}

GameManager::~GameManager() {
  delete player;
  delete questManager;
}

void GameManager::initialize() {
  cout << "=================================\n";
  cout << "     ADVENTURE GAME\n";
  cout << "=================================\n\n";

  string playerName;
  cout << "Enter your hero's name: ";
  getline(cin, playerName);

  player = new Player(playerName, 100, 25);
  questManager = new QuestManager();

  cout << "\nWelcome, " << player->getName() << "!\n";
  cout << "Your adventure begins...\n";
  cout << "\nPress Enter to continue...";
  cin.get();
}

void GameManager::run() {
  while (isRunning && player->isAlive()) {
    displayMainMenu();
    int choice = getChoice(1, 7);
    handleMenuChoice(choice);
  }

  shutdown();
}

void GameManager::displayMainMenu() {
  cout << "\n=== MAIN MENU ===\n";
  cout << "Level " << player->getLevel() << " | "
       << "HP: " << player->getHealth() << "/" << player->getMaxHealth()
       << " | XP: " << player->getExperience() << "/"
       << player->getExperienceToNextLevel() << "\n";
  cout << "Attack: " << player->getAttack()
       << " | Defense: " << player->getDefense()
       << " | Gold: " << player->getGold()
       << " | Potions: " << player->getPotionCount() << "\n\n";
  cout << "Where do you want to go?\n";
  cout << "1. Explore the town\n";
  cout << "2. Venture into the forest\n";
  cout << "3. View quests\n";
  cout << "4. View inventory\n";
  cout << "5. View stats\n";
  cout << "6. Rest (restore HP)\n";
  cout << "7. Quit game\n\n";
}

void GameManager::handleMenuChoice(int choice) {
  if (choice == 1) {
    exploreTown(*player, *questManager);
  } else if (choice == 2) {
    exploreForest(*player, *questManager);
  } else if (choice == 3) {
    questManager->displayActiveQuests();
    questManager->displayCompletedQuests();
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 4) {
    player->displayInventory();
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 5) {
    player->displayStats();
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 6) {
    cout << "\nYou rest at the inn...\n";
    cout << "The night passes peacefully.\n";
    player->heal(player->getMaxHealth());
    cout << "HP fully restored!\n";
    cout << "A new day begins...\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 7) {
    cout << "\nAre you sure you want to quit? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (confirm == 'y' || confirm == 'Y') {
      cout << "\nYour adventure ends here... for now.\n";
      isRunning = false;
    }
  }
}

void GameManager::shutdown() {
  if (!player->isAlive()) {
    cout << "\n=================================\n";
    cout << "      GAME OVER\n";
    cout << "=================================\n";
  } else {
    cout << "\nThanks for playing!\n";
  }
}