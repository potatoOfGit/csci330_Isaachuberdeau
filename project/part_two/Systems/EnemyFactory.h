#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <random>
#include <string>

#include "../Entities/Enemy.h"

class EnemyFactory {
 public:
  virtual ~EnemyFactory() {}
  virtual Enemy* createEnemy() const = 0;
  virtual std::string getDescription() const = 0;
};

class GoblinFactory : public EnemyFactory {
 public:
  Enemy* createEnemy() const override;
  std::string getDescription() const override;
};

class WolfFactory : public EnemyFactory {
 public:
  Enemy* createEnemy() const override;
  std::string getDescription() const override;
};

class BanditFactory : public EnemyFactory {
 public:
  Enemy* createEnemy() const override;
  std::string getDescription() const override;
};

class OrcFactory : public EnemyFactory {
 public:
  Enemy* createEnemy() const override;
  std::string getDescription() const override;
};

class TrollFactory : public EnemyFactory {
 public:
  Enemy* createEnemy() const override;
  std::string getDescription() const override;
};

EnemyFactory* getRandomEnemyFactory();

#endif