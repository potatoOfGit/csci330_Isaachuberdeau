#include <chrono>
#include <iostream>
#include <string>
#include <thread>

class BattleSystem {
 private:
  std::string playerName;
  int playerHP;
  int playerAttack;

  std::string enemyName;
  int enemyHP;
  int enemyAttack;

  void clearScreen() {
    // Cross-platform clear (works on most systems)
    std::cout << "\033[2J\033[1;1H";
  }

  void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  }

  void displayBattle() {
    clearScreen();
    std::cout << "=================================\n";
    std::cout << "         BATTLE ARENA\n";
    std::cout << "=================================\n\n";
    std::cout << playerName << " HP: " << playerHP << "\n";
    std::cout << "          VS\n";
    std::cout << enemyName << " HP: " << enemyHP << "\n\n";
    std::cout << "=================================\n";
  }

 public:
  BattleSystem(std::string pName, int pHP, int pAtk, std::string eName, int eHP,
               int eAtk)
      : playerName(pName),
        playerHP(pHP),
        playerAttack(pAtk),
        enemyName(eName),
        enemyHP(eHP),
        enemyAttack(eAtk) {}

  void battle() {
    while (playerHP > 0 && enemyHP > 0) {
      displayBattle();

      std::cout << "\n[1] Attack\n[2] Defend\n[3] Run\n";
      std::cout << "Choose action: ";

      int choice;
      std::cin >> choice;

      if (choice == 1) {
        // Player attacks
        enemyHP -= playerAttack;
        std::cout << "\n"
                  << playerName << " attacks for " << playerAttack
                  << " damage!\n";
        sleep(1000);

        if (enemyHP <= 0) {
          std::cout << "\nVictory! " << enemyName << " defeated!\n";
          sleep(2000);
          break;
        }

        // Enemy attacks back
        playerHP -= enemyAttack;
        std::cout << enemyName << " counterattacks for " << enemyAttack
                  << " damage!\n";
        sleep(1000);

        if (playerHP <= 0) {
          std::cout << "\nDefeat! You were defeated...\n";
          sleep(2000);
          break;
        }
      } else if (choice == 2) {
        std::cout << "\nYou defend! Damage reduced!\n";
        int reducedDamage = enemyAttack / 2;
        playerHP -= reducedDamage;
        std::cout << enemyName << " attacks for " << reducedDamage
                  << " damage!\n";
        sleep(1000);
      } else if (choice == 3) {
        std::cout << "\nYou ran away!\n";
        sleep(1000);
        break;
      }
    }
  }
};

int main() {
  std::cout << "=== RPG BATTLE SYSTEM ===\n\n";

  BattleSystem battle("Hero", 100, 15, "Goblin", 50, 10);
  battle.battle();

  std::cout << "\nThanks for playing!\n";

  return 0;
}