#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <string>

class Player {
private:
    std::string name;
    CellState symbol;
    int wins;

public:
    Player(const std::string& playerName, CellState playerSymbol);
    ~Player() = default;

    // Геттеры и сеттеры
    std::string getName() const;
    CellState getSymbol() const;
    int getWins() const;
    void addWin();

    // Сохранение/загрузка статистики
    void saveStats(const std::string& filename) const;
    void loadStats(const std::string& filename);
};

#endif // PLAYER_H


