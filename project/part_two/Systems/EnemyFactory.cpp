#include "EnemyFactory.h"

#include <ctime>
#include <vector>

Enemy* GoblinFactory::createEnemy() const {
  return new Enemy("Goblin", 40, 12);
}

std::string GoblinFactory::getDescription() const {
  return "A small, green creature with sharp teeth and a rusty dagger.";
}

Enemy* WolfFactory::createEnemy() const {
  return new Enemy("Wild Wolf", 50, 15);
}

std::string WolfFactory::getDescription() const {
  return "A fierce wolf with glowing eyes and bared fangs.";
}

Enemy* BanditFactory::createEnemy() const {
  return new Enemy("Forest Bandit", 60, 18);
}

std::string BanditFactory::getDescription() const {
  return "A desperate criminal wielding a worn sword.";
}

Enemy* OrcFactory::createEnemy() const {
  return new Enemy("Orc Warrior", 80, 22);
}

std::string OrcFactory::getDescription() const {
  return "A muscular orc brandishing a massive axe.";
}

Enemy* TrollFactory::createEnemy() const {
  return new Enemy("Forest Troll", 100, 25);
}

std::string TrollFactory::getDescription() const {
  return "A towering troll with thick, mossy skin and enormous strength.";
}

EnemyFactory* getRandomEnemyFactory() {
  static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
  std::uniform_int_distribution<int> dist(0, 4);

  int random = dist(rng);

  switch (random) {
    case 0:
      return new GoblinFactory();
    case 1:
      return new WolfFactory();
    case 2:
      return new BanditFactory();
    case 3:
      return new OrcFactory();
    case 4:
      return new TrollFactory();
    default:
      return new GoblinFactory();
  }
}