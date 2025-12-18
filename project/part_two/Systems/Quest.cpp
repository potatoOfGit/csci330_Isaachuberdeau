#include "Quest.h"

#include <iostream>

#include "../Entities/Player.h"

Quest::Quest(const std::string& name, const std::string& desc, int needed,
             int reward)
    : questName(name),
      description(desc),
      enemiesKilled(0),
      enemiesNeeded(needed),
      isCompleted(false),
      goldReward(reward) {}

void Quest::incrementProgress() {
  if (!isCompleted) {
    enemiesKilled++;
    std::cout << "Quest Progress: " << questName << " (" << enemiesKilled << "/"
              << enemiesNeeded << ")\n";
  }
}

bool Quest::checkComplete() {
  if (!isCompleted && enemiesKilled >= enemiesNeeded) {
    return true;
  }
  return false;
}

void Quest::markComplete() { isCompleted = true; }

std::string Quest::getName() const { return questName; }

std::string Quest::getDescription() const { return description; }

int Quest::getProgress() const { return enemiesKilled; }

int Quest::getTarget() const { return enemiesNeeded; }

bool Quest::isComplete() const { return isCompleted; }

int Quest::getReward() const { return goldReward; }

void QuestManager::addQuest(const Quest& quest) {
  activeQuests.push_back(quest);
  std::cout << "\nNew Quest Added: " << quest.getName() << "\n";
  std::cout << quest.getDescription() << "\n";
}

void QuestManager::updateQuestProgress(const std::string& enemyType) {
  for (auto& quest : activeQuests) {
    if (!quest.isComplete()) {
      quest.incrementProgress();
    }
  }
}

void QuestManager::displayActiveQuests() const {
  if (activeQuests.empty()) {
    std::cout << "No active quests.\n";
    return;
  }

  std::cout << "\n=== ACTIVE QUESTS ===\n";
  for (const auto& quest : activeQuests) {
    std::cout << "- " << quest.getName() << ": " << quest.getDescription()
              << "\n";
    std::cout << "  Progress: " << quest.getProgress() << "/"
              << quest.getTarget();
    if (quest.isComplete()) {
      std::cout << " [READY TO TURN IN]";
    }
    std::cout << "\n  Reward: " << quest.getReward() << " gold\n\n";
  }
}

void QuestManager::displayCompletedQuests() const {
  if (completedQuests.empty()) {
    std::cout << "No completed quests yet.\n";
    return;
  }

  std::cout << "\n=== COMPLETED QUESTS ===\n";
  for (const auto& quest : completedQuests) {
    std::cout << "- " << quest.getName() << " [COMPLETED]\n";
  }
  std::cout << "\n";
}

bool QuestManager::hasActiveQuests() const { return !activeQuests.empty(); }

void QuestManager::checkAndCompleteQuests(Player& player) {
  bool anyCompleted = false;

  for (auto it = activeQuests.begin(); it != activeQuests.end();) {
    if (it->checkComplete()) {
      std::cout << "\n*** QUEST COMPLETE: " << it->getName() << " ***\n";
      std::cout << "Reward: " << it->getReward() << " gold\n\n";

      player.addGold(it->getReward());

      it->markComplete();
      completedQuests.push_back(*it);
      it = activeQuests.erase(it);
      anyCompleted = true;
    } else {
      ++it;
    }
  }

  if (!anyCompleted && hasActiveQuests()) {
    std::cout << "You have active quests to complete!\n";
  }
}