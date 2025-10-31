#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <vector>

enum class CellState {
    EMPTY = 0,
    X = 1,
    O = 2
};

class Board {
private:
    static const int SIZE = 3;
    CellState grid[SIZE][SIZE];
    int moveCount;

public:
    Board();
    ~Board() = default;

    // Основные операции с доской
    bool makeMove(int row, int col, CellState player);
    bool isValidMove(int row, int col) const;
    bool isFull() const;
    bool checkWin(CellState player) const;
    void clear();
    
    // Геттеры
    CellState getCell(int row, int col) const;
    int getMoveCount() const;
    int getSize() const { return SIZE; }

    // Файловый ввод/вывод
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Отображение (для консоли)
    void display() const;
    
    // Получение состояния для GUI
    std::vector<std::vector<CellState>> getGridState() const;
};

#endif // BOARD_H


