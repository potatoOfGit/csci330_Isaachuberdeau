#include "Forest.h"

#include <iostream>

#include "../../Entities/Enemy.h"
#include "../../Systems/Combat.h"
#include "../../Systems/EnemyFactory.h"
#include "../../Systems/InputUtils.h"
#include "Dungeon.h"

using namespace std;

void exploreForest(Player& player, QuestManager& questManager) {
  bool inForest = true;
  int enemiesDefeated = 0;
  const int ENEMIES_REQUIRED = 3;

  while (inForest && player.isAlive()) {
    cout << "\n=== DARK FOREST ===\n";
    cout << "You venture into the mysterious forest.\n";
    cout << "The trees loom overhead, blocking out the sunlight.\n";

    if (enemiesDefeated >= ENEMIES_REQUIRED) {
      cout << "You notice a dark cave entrance hidden behind the trees...\n";
    }

    cout << "\nEnemies defeated on path: " << enemiesDefeated << "/"
         << ENEMIES_REQUIRED << "\n\n";

    cout << "What do you do?\n";
    cout << "1. Follow the path deeper\n";
    cout << "2. Search the bushes\n";
    cout << "3. Use a potion (Potions: " << player.getPotionCount() << ")\n";

    if (enemiesDefeated >= ENEMIES_REQUIRED) {
      cout << "4. Enter the dungeon\n";
      cout << "5. Return to safety\n\n";
    } else {
      cout << "4. Return to safety\n\n";
    }

    int maxChoice = (enemiesDefeated >= ENEMIES_REQUIRED) ? 5 : 4;
    int choice = getChoice(1, maxChoice);

    if (choice == 1) {
      cout << "\nYou walk deeper into the forest...\n";
      cout << "Suddenly, you hear a sound!\n";

      EnemyFactory* factory = getRandomEnemyFactory();
      Enemy* enemy = factory->createEnemy();

      cout << factory->getDescription() << "\n";
      cout << "A " << enemy->getName() << " appears!\n";
      cout << "\nPress Enter to continue...";
      cin.get();

      startBattle(player, *enemy);

      if (player.isAlive() && !enemy->isAlive()) {
        cout << "\nYou defeated the " << enemy->getName() << "!\n";
        questManager.updateQuestProgress(enemy->getName());
        enemiesDefeated++;

        if (enemiesDefeated == ENEMIES_REQUIRED) {
          cout << "\nYou've cleared the forest path! A dark cave entrance is "
                  "now visible.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
      } else if (!player.isAlive()) {
        inForest = false;
      }

      delete enemy;
      delete factory;

    } else if (choice == 2) {
      cout << "\nYou search through the bushes...\n";
      cout << "You find some herbs! (But you can't use them yet)\n";
      cout << "\nPress Enter to continue...";
      cin.get();
    } else if (choice == 3) {
      player.usePotion();
      cout << "\nPress Enter to continue...";
      cin.get();
    } else if (choice == 4 && enemiesDefeated >= ENEMIES_REQUIRED) {
      cout << "\nYou approach the dark cave entrance...\n";
      cout << "Press Enter to continue...";
      cin.get();

      exploreDungeon(player, questManager);

      if (player.isAlive()) {
        cout << "\nYou emerge from the dungeon back into the forest.\n";
        cout << "Press Enter to continue...";
        cin.get();
      } else {
        inForest = false;
      }
    } else {
      cout << "\nYou carefully make your way back.\n";
      cout << "\nPress Enter to continue...";
      cin.get();
      inForest = false;
    }
  }
}