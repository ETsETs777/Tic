#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <memory>

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    PAUSED
};

class Game {
private:
    Board board;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    Player* currentPlayer;
    GameState state;
    CellState winner;
    bool isDraw;

    void switchPlayer();
    void checkGameOver();

public:
    Game();
    ~Game() = default;

    // Управление игрой
    void startNewGame(const std::string& player1Name, const std::string& player2Name);
    bool makeMove(int row, int col);
    void reset();

    // Геттеры
    GameState getState() const;
    Player* getCurrentPlayer() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    Board& getBoard();
    CellState getWinner() const;
    bool getIsDraw() const;

    // Сохранение/загрузка игры
    bool saveGame(const std::string& filename) const;
    bool loadGame(const std::string& filename);
};

#endif // GAME_H


