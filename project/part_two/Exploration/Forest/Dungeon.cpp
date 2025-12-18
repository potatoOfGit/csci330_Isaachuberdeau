#include "Dungeon.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

#include "../../Entities/Enemy.h"
#include "../../Systems/Combat.h"
#include "../../Systems/EnemyFactory.h"
#include "../../Systems/Shop.H"

using namespace std;

Dungeon::Dungeon(int r, int c)
    : rows(r), cols(c), playerRow(0), playerCol(0), bossDefeated(false) {
  grid.resize(rows, vector<Cell>(cols));
  initializeGrid();
}

void Dungeon::initializeGrid() {
  srand(time(0));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      grid[i][j].visited = false;

      int random = rand() % 100;

      if (i == 0 && j == 0) {
        grid[i][j].type = CellType::EMPTY;
        grid[i][j].description =
            "The entrance to the dungeon. You can still turn back...";
      } else if (i == rows - 1 && j == cols - 1) {
        grid[i][j].type = CellType::BOSS;
        grid[i][j].description =
            "A massive door looms before you. You sense great danger beyond.";
      } else if (i == 0 && j == cols - 1) {
        grid[i][j].type = CellType::EXIT;
        grid[i][j].description = "A ladder leading back to the surface!";
      } else if (random < 40) {
        grid[i][j].type = CellType::ENEMY;
        grid[i][j].description = "You hear movement in the shadows...";
      } else if (random < 50) {
        grid[i][j].type = CellType::WEAPON;
        grid[i][j].description = "Something glints in the torchlight.";
      } else {
        grid[i][j].type = CellType::EMPTY;
        grid[i][j].description = "An empty chamber. You catch your breath.";
      }
    }
  }

  grid[0][0].visited = true;
}

void Dungeon::displayMap() const {
  cout << "\n=== DUNGEON MAP ===\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == playerRow && j == playerCol) {
        cout << "[@]";
      } else if (grid[i][j].visited) {
        switch (grid[i][j].type) {
          case CellType::EMPTY:
            cout << "[ ]";
            break;
          case CellType::ENEMY:
            cout << "[X]";
            break;
          case CellType::WEAPON:
            cout << "[W]";
            break;
          case CellType::BOSS:
            cout << "[B]";
            break;
          case CellType::EXIT:
            cout << "[E]";
            break;
          default:
            cout << "[ ]";
            break;
        }
      } else {
        cout << "[?]";
      }
    }
    cout << "\n";
  }
  cout << "\n[@] = You  [X] = Enemy  [W] = Weapon  [B] = Boss  [E] = Exit  [?] "
          "= Unknown\n";
}

void Dungeon::displayCurrentRoom() const {
  cout << "\n" << grid[playerRow][playerCol].description << "\n";
}

void Dungeon::handleCell(Player& player, QuestManager& questManager) {
  Cell& current = grid[playerRow][playerCol];

  if (current.visited && current.type != CellType::BOSS) {
    return;
  }

  current.visited = true;

  switch (current.type) {
    case CellType::ENEMY: {
      cout << "\nAn enemy attacks!\n";
      cout << "Press Enter to continue...";
      cin.get();

      EnemyFactory* factory = getRandomEnemyFactory();
      Enemy* enemy = factory->createEnemy();

      startBattle(player, *enemy);

      if (!enemy->isAlive()) {
        cout << "\nYou defeated the " << enemy->getName() << "!\n";
        current.type = CellType::EMPTY;
        current.description = "The remains of a defeated enemy.";
      }

      delete enemy;
      delete factory;
      break;
    }

    case CellType::WEAPON: {
      cout << "\nYou found a weapon!\n";
      Item dungeon_weapon = {"Dungeon Blade",
                             "A weapon forged in darkness (+15 attack)", 0,
                             "weapon", 15};
      player.equipWeapon(dungeon_weapon);
      current.type = CellType::EMPTY;
      current.description = "Where you found a weapon.";
      cout << "\nPress Enter to continue...";
      cin.get();
      break;
    }

    case CellType::BOSS: {
      if (bossDefeated) {
        cout << "\nThe boss chamber is empty. Only bones remain.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
      }

      cout << "\n=== BOSS FIGHT ===\n";
      cout << "A massive DUNGEON LORD emerges from the darkness!\n";
      cout << "This is it - defeat him or perish!\n";
      cout << "Press Enter to continue...";
      cin.get();

      Enemy boss("Dungeon Lord", 150, 30);
      startBattle(player, boss);

      if (!boss.isAlive()) {
        cout << "\n*** YOU DEFEATED THE DUNGEON LORD! ***\n";
        cout << "You found 500 gold in the boss's treasure!\n";
        player.addGold(500);
        bossDefeated = true;
        current.description =
            "The defeated boss lies here. You are victorious!";
      }
      cout << "\nPress Enter to continue...";
      cin.get();
      break;
    }

    default:
      break;
  }
}

bool Dungeon::move(char direction, Player& player, QuestManager& questManager) {
  int newRow = playerRow;
  int newCol = playerCol;

  switch (direction) {
    case 'w':
      newRow--;
      break;
    case 's':
      newRow++;
      break;
    case 'a':
      newCol--;
      break;
    case 'd':
      newCol++;
      break;
    default:
      return false;
  }

  if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
    cout << "You can't go that way! There's a wall.\n";
    return false;
  }

  playerRow = newRow;
  playerCol = newCol;

  displayCurrentRoom();
  handleCell(player, questManager);

  return player.isAlive();
}

bool Dungeon::canExit() const {
  return playerRow == 0 && playerCol == (cols - 1);
}

void exploreDungeon(Player& player, QuestManager& questManager) {
  Dungeon dungeon(5, 5);

  cout << "\n=== ENTERING THE DUNGEON ===\n";
  cout << "You descend into the dark dungeon...\n";
  cout << "Navigate using WASD (W=North, S=South, A=West, D=East)\n";
  cout << "\nPress Enter to continue...";
  cin.get();

  bool inDungeon = true;

  while (inDungeon && player.isAlive()) {
    dungeon.displayMap();
    dungeon.displayCurrentRoom();

    cout << "\nHP: " << player.getHealth() << "/" << player.getMaxHealth()
         << " | Potions: " << player.getPotionCount() << "\n";

    if (dungeon.canExit()) {
      cout << "\nYou're at the exit! Press 'e' to leave the dungeon.\n";
    }

    cout << "\nMove (WASD) or use Potion (p) or Exit (e if at exit): ";

    char input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (input == 'p') {
      player.usePotion();
      cout << "\nPress Enter to continue...";
      cin.get();
    } else if (input == 'e' && dungeon.canExit()) {
      cout << "\nYou climb out of the dungeon!\n";
      cout << "\nPress Enter to continue...";
      cin.get();
      inDungeon = false;
    } else if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
      if (!dungeon.move(input, player, questManager)) {
        if (!player.isAlive()) {
          cout << "\nYou have fallen in the dungeon...\n";
        }
      }
      if (player.isAlive()) {
        cout << "\nPress Enter to continue...";
        cin.get();
      }
    } else {
      cout << "Invalid input!\n";
    }
  }
}