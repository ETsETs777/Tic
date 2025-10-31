#include "Game.h"
#include <fstream>
#include <algorithm>

Game::Game() : currentPlayer(nullptr), state(GameState::MENU), 
               winner(CellState::EMPTY), isDraw(false) {
}

void Game::startNewGame(const std::string& player1Name, const std::string& player2Name) {
    board.clear();
    player1 = std::make_unique<Player>(player1Name, CellState::X);
    player2 = std::make_unique<Player>(player2Name, CellState::O);
    currentPlayer = player1.get();
    state = GameState::PLAYING;
    winner = CellState::EMPTY;
    isDraw = false;
}

bool Game::makeMove(int row, int col) {
    if (state != GameState::PLAYING || currentPlayer == nullptr) {
        return false;
    }

    if (board.makeMove(row, col, currentPlayer->getSymbol())) {
        checkGameOver();
        if (state == GameState::PLAYING) {
            switchPlayer();
        }
        return true;
    }
    return false;
}

void Game::switchPlayer() {
    if (currentPlayer == player1.get()) {
        currentPlayer = player2.get();
    } else {
        currentPlayer = player1.get();
    }
}

void Game::checkGameOver() {
    if (board.checkWin(currentPlayer->getSymbol())) {
        state = GameState::GAME_OVER;
        winner = currentPlayer->getSymbol();
        currentPlayer->addWin();
    } else if (board.isFull()) {
        state = GameState::GAME_OVER;
        isDraw = true;
        winner = CellState::EMPTY;
    }
}

void Game::reset() {
    board.clear();
    if (player1 && player2) {
        currentPlayer = player1.get();
        state = GameState::PLAYING;
        winner = CellState::EMPTY;
        isDraw = false;
    }
}

GameState Game::getState() const {
    return state;
}

Player* Game::getCurrentPlayer() const {
    return currentPlayer;
}

Player* Game::getPlayer1() const {
    return player1.get();
}

Player* Game::getPlayer2() const {
    return player2.get();
}

Board& Game::getBoard() {
    return board;
}

CellState Game::getWinner() const {
    return winner;
}

bool Game::getIsDraw() const {
    return isDraw;
}

bool Game::saveGame(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Сохраняем доску
    std::string boardFile = filename + "_board.dat";
    if (!board.saveToFile(boardFile)) {
        file.close();
        return false;
    }

    // Сохраняем информацию об игре
    file << static_cast<int>(state) << "\n";
    file << static_cast<int>(winner) << "\n";
    file << (isDraw ? 1 : 0) << "\n";
    
    if (player1 && player2) {
        file << player1->getName() << "\n";
        file << player2->getName() << "\n";
        file << (currentPlayer == player1.get() ? 1 : 2) << "\n";
    }

    file.close();
    return true;
}

bool Game::loadGame(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Загружаем доску
    std::string boardFile = filename + "_board.dat";
    if (!board.loadFromFile(boardFile)) {
        file.close();
        return false;
    }

    // Загружаем информацию об игре
    int stateInt, winnerInt, drawInt;
    file >> stateInt >> winnerInt >> drawInt;
    state = static_cast<GameState>(stateInt);
    winner = static_cast<CellState>(winnerInt);
    isDraw = (drawInt == 1);

    if (state != GameState::MENU) {
        std::string p1Name, p2Name;
        int currentPlayerNum;
        file >> p1Name >> p2Name >> currentPlayerNum;
        
        player1 = std::make_unique<Player>(p1Name, CellState::X);
        player2 = std::make_unique<Player>(p2Name, CellState::O);
        currentPlayer = (currentPlayerNum == 1) ? player1.get() : player2.get();
    }

    file.close();
    return true;
}


