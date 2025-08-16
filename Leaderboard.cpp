#include "SkipList.h"
#include <iostream>
#include <string>
#include <vector>

void printMenu() {
    std::cout << "\n=== Skip List Leaderboard ===\n";
    std::cout << "1) Add/Update Player\n";
    std::cout << "2) Remove Player\n";
    std::cout << "3) Get Rank\n";
    std::cout << "4) Show Top N\n";
    std::cout << "5) Show All\n";
    std::cout << "6) Quit\n";
    std::cout << "Choose: ";
}

int main() {
    SkipList leaderboard;

    while (true) {
        printMenu();

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            int score;
            std::cout << "Player name: ";
            std::cin >> name;
            std::cout << "Score: ";
            std::cin >> score;
            leaderboard.insert(name, score);
            std::cout << "Added/Updated " << name << " with score " << score << ".\n";

        } else if (choice == 2) {
            std::string name;
            std::cout << "Player name: ";
            std::cin >> name;
            bool removed = leaderboard.remove(name);
            if (removed) {
                std::cout << "Player removed.\n";
            } else {
                std::cout << "Player not found.\n";
            }

        } else if (choice == 3) {
            std::string name;
            std::cout << "Player name: ";
            std::cin >> name;

            size_t rank = leaderboard.getRank(name);
            int score = leaderboard.getScore(name);

            if (rank != 0) {
                std::cout << name << " is ranked #" << rank 
                        << " with score " << score << "\n";
            } else {
                std::cout << name << " not found on leaderboard.\n";
            }

        } else if (choice == 4) {
            int n;
            std::cout << "Number of top players to show: ";
            std::cin >> n;

            std::vector<Player> topPlayers = leaderboard.topN(n);
            for (size_t i = 0; i < topPlayers.size(); i++) {
                std::cout << i << ") " << topPlayers[i].name
                          << " : " << topPlayers[i].score << "\n";
            }

        } else if (choice == 5) {
            std::vector<Player> allPlayers = leaderboard.all();
            for (size_t i = 0; i < allPlayers.size(); i++) {
                std::cout << i << ") " << allPlayers[i].name
                          << " : " << allPlayers[i].score << "\n";
            }

        } else if (choice == 6) {
            std::cout << "Goodbye!\n";
            break;

        } else {
            std::cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
