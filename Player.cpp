#include "Player.h"
#include <fstream>
#include <sstream>

Player::Player(const std::string& playerName, CellState playerSymbol)
    : name(playerName), symbol(playerSymbol), wins(0) {
}

std::string Player::getName() const {
    return name;
}

CellState Player::getSymbol() const {
    return symbol;
}

int Player::getWins() const {
    return wins;
}

void Player::addWin() {
    wins++;
}

void Player::saveStats(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << name << "," << static_cast<int>(symbol) << "," << wins << "\n";
        file.close();
    }
}

void Player::loadStats(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string savedName;
            std::string symbolStr;
            std::string winsStr;
            
            if (std::getline(iss, savedName, ',') &&
                std::getline(iss, symbolStr, ',') &&
                std::getline(iss, winsStr)) {
                if (savedName == name && std::stoi(symbolStr) == static_cast<int>(symbol)) {
                    wins = std::stoi(winsStr);
                    break;
                }
            }
        }
        file.close();
    }
}


