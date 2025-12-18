#ifndef QUEST_H
#define QUEST_H

#include <string>
#include <vector>

class Player;

class Quest {
 private:
  std::string questName;
  std::string description;
  int enemiesKilled;
  int enemiesNeeded;
  bool isCompleted;
  int goldReward;

 public:
  Quest(const std::string& name, const std::string& desc, int enemiesNeeded,
        int reward);

  void incrementProgress();
  bool checkComplete();
  void markComplete();

  std::string getName() const;
  std::string getDescription() const;
  int getProgress() const;
  int getTarget() const;
  bool isComplete() const;
  int getReward() const;
};

class QuestManager {
 private:
  std::vector<Quest> activeQuests;
  std::vector<Quest> completedQuests;

 public:
  void addQuest(const Quest& quest);
  void updateQuestProgress(const std::string& enemyType);
  void displayActiveQuests() const;
  void displayCompletedQuests() const;
  bool hasActiveQuests() const;
  void checkAndCompleteQuests(Player& player);
};

#endif