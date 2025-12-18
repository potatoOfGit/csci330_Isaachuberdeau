#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>
#include <vector>

#include "../../Entities/Player.h"
#include "../../Systems/Quest.h"

enum class CellType { EMPTY, ENEMY, WEAPON, BOSS, EXIT, WALL };

struct Cell {
  CellType type;
  bool visited;
  std::string description;
};

class Dungeon {
 private:
  std::vector<std::vector<Cell>> grid;
  int playerRow;
  int playerCol;
  int rows;
  int cols;
  bool bossDefeated;

 public:
  Dungeon(int r, int c);
  void displayMap() const;
  void displayCurrentRoom() const;
  bool move(char direction, Player& player, QuestManager& questManager);
  bool canExit() const;

 private:
  void initializeGrid();
  void handleCell(Player& player, QuestManager& questManager);
};

void exploreDungeon(Player& player, QuestManager& questManager);

#endif