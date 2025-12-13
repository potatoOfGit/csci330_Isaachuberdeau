#include <iostream>
#include <limits>

#include "Combat.h"

using namespace std;

void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getChoice(int min, int max) {
  int choice;
  while (true) {
    cout << "Enter your choice: ";
    if (cin >> choice && choice >= min && choice <= max) {
      clearInput();
      return choice;
    } else {
      cout << "Invalid choice! Try again.\n";
      clearInput();
    }
  }
}

void exploreTown(Player& player) {
  cout << "\n=== TOWN ===\n";
  cout << "You walk through the peaceful town square.\n";
  cout << "Merchants are selling their wares and children are playing.\n\n";

  cout << "Where do you want to go?\n";
  cout << "1. Visit the blacksmith\n";
  cout << "2. Go to the tavern\n";
  cout << "3. Leave town\n\n";

  int choice = getChoice(1, 3);

  if (choice == 1) {
    cout << "\nThe blacksmith greets you warmly.\n";
    cout << "\"Welcome, traveler! Stay safe out there.\"\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  } else if (choice == 2) {
    cout << "\nYou enter the cozy tavern.\n";
    cout << "The bartender tells you about strange creatures in the forest.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  } else {
    cout << "\nYou leave the safety of the town.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  }
}

void exploreForest(Player& player) {
  cout << "\n=== DARK FOREST ===\n";
  cout << "You venture into the mysterious forest.\n";
  cout << "The trees loom overhead, blocking out the sunlight.\n\n";

  cout << "What do you do?\n";
  cout << "1. Follow the path deeper\n";
  cout << "2. Search the bushes\n";
  cout << "3. Return to safety\n\n";

  int choice = getChoice(1, 3);

  if (choice == 1) {
    cout << "\nYou walk deeper into the forest...\n";
    cout << "Suddenly, you hear a growl!\n";
    cout << "A wild goblin appears!\n";
    cout << "\nPress Enter to continue...";
    cin.get();

    Enemy goblin("Goblin", 50, 15);
    startBattle(player, goblin);

  } else if (choice == 2) {
    cout << "\nYou search through the bushes...\n";
    cout << "You find a small potion! (But you can't use it yet)\n";
    cout << "\nPress Enter to continue...";
    cin.get();
  } else {
    cout << "\nYou carefully make your way back.\n";
    cout << "\nPress Enter to continue...";
    cin.get();
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

  cout << "\nWelcome, " << hero.getName() << "!\n";
  cout << "Your adventure begins...\n";
  cout << "\nPress Enter to continue...";
  cin.get();

  bool playing = true;

  while (playing && hero.isAlive()) {
    cout << "\n=== MAIN MENU ===\n";
    cout << "HP: " << hero.getHealth() << "\n\n";
    cout << "Where do you want to go?\n";
    cout << "1. Explore the town\n";
    cout << "2. Venture into the forest\n";
    cout << "3. Rest (end game)\n\n";

    int choice = getChoice(1, 3);

    if (choice == 1) {
      exploreTown(hero);
    } else if (choice == 2) {
      exploreForest(hero);
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