#include <iostream>

#include "Combat.h"

using namespace std;

int main() {
  Player hero("Hero", 100, 25);
  Enemy goblin("Goblin", 50, 15);

  startBattle(hero, goblin);

  return 0;
}