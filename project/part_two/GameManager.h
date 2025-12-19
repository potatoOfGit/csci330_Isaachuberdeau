#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Entities/Player.h"
#include "Systems/Quest.h"

class GameManager {
 private:
  Player* player;
  QuestManager* questManager;
  bool isRunning;

 public:
  GameManager();
  ~GameManager();

  void initialize();
  void run();
  void displayMainMenu();
  void handleMenuChoice(int choice);
  void shutdown();
};

#endif