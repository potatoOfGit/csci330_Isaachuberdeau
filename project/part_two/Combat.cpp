#include "Combat.h"

#include <iostream>
#include <limits>

using namespace std;

void displayStatus(const Player& player, const Enemy& enemy) {
  cout << "\n=================================\n";
  cout << player.getName() << " HP: " << player.getHealth() << "\n";
  cout << enemy.getName() << " HP: " << enemy.getHealth() << "\n";
  cout << "=================================\n";
}

int getPlayerChoice() {
  int choice;
  while (true) {
    cout << "\nChoose your action:\n";
    cout << "1. Attack\n";
    cout << "2. Defend (reduce damage by half next turn)\n";
    cout << "Enter choice (1-2): ";

    if (cin >> choice && choice >= 1 && choice <= 2) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return choice;
    } else {
      cout << "Invalid input! Please enter 1 or 2.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void startBattle(Player& hero, Enemy& enemy) {
  bool isDefending = false;

  cout << "\nBattle begins!\n";

  while (hero.isAlive() && enemy.isAlive()) {
    displayStatus(hero, enemy);

    int choice = getPlayerChoice();

    if (choice == 1) {
      hero.attackEnemy(enemy);
      cout << enemy.getName() << " health: " << enemy.getHealth() << "\n\n";
    } else if (choice == 2) {
      cout << "\n" << hero.getName() << " takes a defensive stance!\n\n";
      isDefending = true;
    }

    if (!enemy.isAlive()) {
      break;
    }

    int damage = enemy.getAttack();

    if (isDefending) {
      damage /= 2;
      cout << enemy.getName() << " attacks for " << enemy.getAttack()
           << " damage!\n";
      cout << hero.getName() << " blocks half the damage!\n";
      hero.takeDamage(damage);
      isDefending = false;
    } else {
      enemy.attackPlayer(hero);
    }

    cout << hero.getName() << " health: " << hero.getHealth() << "\n\n";

    cout << "Press Enter to continue...";
    cin.get();
  }

  cout << "\n";
  if (hero.isAlive()) {
    cout << hero.getName() << " wins!\n";
  } else {
    cout << enemy.getName() << " wins!\n";
  }
}