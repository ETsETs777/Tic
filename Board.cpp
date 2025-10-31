#include "Board.h"
#include <fstream>

Board::Board() : moveCount(0) {
    clear();
}

void Board::clear() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = CellState::EMPTY;
        }
    }
    moveCount = 0;
}

bool Board::isValidMove(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }
    return grid[row][col] == CellState::EMPTY;
}

bool Board::makeMove(int row, int col, CellState player) {
    if (!isValidMove(row, col)) {
        return false;
    }
    grid[row][col] = player;
    moveCount++;
    return true;
}

bool Board::isFull() const {
    return moveCount >= SIZE * SIZE;
}

bool Board::checkWin(CellState player) const {
    // Проверка строк
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) {
            return true;
        }
    }

    // Проверка столбцов
    for (int j = 0; j < SIZE; j++) {
        if (grid[0][j] == player && grid[1][j] == player && grid[2][j] == player) {
            return true;
        }
    }

    // Проверка главной диагонали
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) {
        return true;
    }

    // Проверка побочной диагонали
    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) {
        return true;
    }

    return false;
}

CellState Board::getCell(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return CellState::EMPTY;
    }
    return grid[row][col];
}

int Board::getMoveCount() const {
    return moveCount;
}

void Board::display() const {
    std::cout << "\n  0 1 2\n";
    for (int i = 0; i < SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            switch (grid[i][j]) {
                case CellState::EMPTY:
                    std::cout << ". ";
                    break;
                case CellState::X:
                    std::cout << "X ";
                    break;
                case CellState::O:
                    std::cout << "O ";
                    break;
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<std::vector<CellState>> Board::getGridState() const {
    std::vector<std::vector<CellState>> state(SIZE, std::vector<CellState>(SIZE));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            state[i][j] = grid[i][j];
        }
    }
    return state;
}

bool Board::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Сохраняем размер доски
    file.write(reinterpret_cast<const char*>(&SIZE), sizeof(SIZE));
    
    // Сохраняем состояние доски
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int cellValue = static_cast<int>(grid[i][j]);
            file.write(reinterpret_cast<const char*>(&cellValue), sizeof(cellValue));
        }
    }

    // Сохраняем количество ходов
    file.write(reinterpret_cast<const char*>(&moveCount), sizeof(moveCount));

    file.close();
    return true;
}

bool Board::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    int savedSize;
    file.read(reinterpret_cast<char*>(&savedSize), sizeof(savedSize));
    
    if (savedSize != SIZE) {
        file.close();
        return false;
    }

    // Загружаем состояние доски
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int cellValue;
            file.read(reinterpret_cast<char*>(&cellValue), sizeof(cellValue));
            grid[i][j] = static_cast<CellState>(cellValue);
        }
    }

    // Загружаем количество ходов
    file.read(reinterpret_cast<char*>(&moveCount), sizeof(moveCount));

    file.close();
    return true;
}


