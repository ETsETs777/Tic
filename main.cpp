#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "Game.h"

class TicTacToeGUI {
private:
    sf::RenderWindow window;
    Game game;
    sf::Font font;
    
    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 700;
    const int BOARD_SIZE = 450;
    const int CELL_SIZE = 150;
    const int BOARD_OFFSET_X = 75;
    const int BOARD_OFFSET_Y = 150;
    
    bool isMenuActive;
    bool isNameInputActive;
    std::string player1Name;
    std::string player2Name;
    int currentNameInput; // 0 - игрок 1, 1 - игрок 2
    
    void handleMenuInput(sf::Event& event);
    void handleGameInput(sf::Event& event);
    void handleNameInput(sf::Event& event);
    void drawMenu();
    void drawGame();
    void drawNameInput();
    void drawBoard();
    void drawGameOver();
    sf::Vector2i getCellFromMouse(int mouseX, int mouseY);
    bool loadFont();

public:
    TicTacToeGUI();
    ~TicTacToeGUI() = default;
    
    void run();
};

TicTacToeGUI::TicTacToeGUI() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic-Tac-Toe"),
      isMenuActive(true), isNameInputActive(false), currentNameInput(0),
      player1Name("Игрок 1"), player2Name("Игрок 2") {
    window.setFramerateLimit(60);
    loadFont();
}

bool TicTacToeGUI::loadFont() {
    // Попытка загрузить системный шрифт
    if (!font.loadFromFile("arial.ttf")) {
        // Пробуем альтернативные пути
        std::vector<std::string> fontPaths = {
            "C:/Windows/Fonts/arial.ttf",
            "C:/Windows/Fonts/calibri.ttf",
            "/usr/share/fonts/truetype/arial.ttf",
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/Library/Fonts/Arial.ttf"
        };
        
        bool loaded = false;
        for (const auto& path : fontPaths) {
            if (font.loadFromFile(path)) {
                loaded = true;
                break;
            }
        }
        
        if (!loaded) {
            std::cout << "Предупреждение: Не удалось загрузить шрифт. Текст может не отображаться корректно.\n";
            std::cout << "Пожалуйста, поместите файл arial.ttf в директорию с исполняемым файлом.\n";
            return false;
        }
    }
    return true;
}

sf::Vector2i TicTacToeGUI::getCellFromMouse(int mouseX, int mouseY) {
    if (mouseX < BOARD_OFFSET_X || mouseX > BOARD_OFFSET_X + BOARD_SIZE ||
        mouseY < BOARD_OFFSET_Y || mouseY > BOARD_OFFSET_Y + BOARD_SIZE) {
        return sf::Vector2i(-1, -1);
    }
    
    int col = (mouseX - BOARD_OFFSET_X) / CELL_SIZE;
    int row = (mouseY - BOARD_OFFSET_Y) / CELL_SIZE;
    
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return sf::Vector2i(row, col);
    }
    return sf::Vector2i(-1, -1);
}

void TicTacToeGUI::handleMenuInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;
        
        // Кнопка "Новая игра"
        if (mouseX >= 200 && mouseX <= 400 && mouseY >= 300 && mouseY <= 350) {
            isNameInputActive = true;
            currentNameInput = 0;
        }
        // Кнопка "Загрузить игру"
        else if (mouseX >= 200 && mouseX <= 400 && mouseY >= 370 && mouseY <= 420) {
            if (game.loadGame("savegame.txt")) {
                isMenuActive = false;
            }
        }
        // Кнопка "Выход"
        else if (mouseX >= 200 && mouseX <= 400 && mouseY >= 440 && mouseY <= 490) {
            window.close();
        }
    }
}

void TicTacToeGUI::handleNameInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            if (currentNameInput == 0) {
                currentNameInput = 1;
            } else {
                game.startNewGame(player1Name, player2Name);
                isNameInputActive = false;
                isMenuActive = false;
            }
        } else if (event.key.code == sf::Keyboard::Escape) {
            isNameInputActive = false;
        } else if (event.key.code == sf::Keyboard::BackSpace) {
            if (currentNameInput == 0 && !player1Name.empty()) {
                player1Name.pop_back();
            } else if (currentNameInput == 1 && !player2Name.empty()) {
                player2Name.pop_back();
            }
        }
    } else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode != 13) {
            char c = static_cast<char>(event.text.unicode);
            if (currentNameInput == 0) {
                player1Name += c;
            } else {
                player2Name += c;
            }
        }
    }
}

void TicTacToeGUI::handleGameInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && 
        game.getState() == GameState::PLAYING) {
        sf::Vector2i cell = getCellFromMouse(event.mouseButton.x, event.mouseButton.y);
        if (cell.x != -1 && cell.y != -1) {
            game.makeMove(cell.x, cell.y);
        }
    }
    
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (game.getState() == GameState::GAME_OVER) {
                isMenuActive = true;
                game.reset();
            } else {
                game.saveGame("savegame.txt");
            }
        } else if (event.key.code == sf::Keyboard::R && 
                   game.getState() == GameState::GAME_OVER) {
            game.reset();
        }
    }
}

void TicTacToeGUI::drawMenu() {
    window.clear(sf::Color(240, 240, 240));
    
    // Заголовок
    sf::Text title("КРЕСТИКИ-НОЛИКИ", font, 48);
    title.setFillColor(sf::Color::Black);
    title.setPosition(120, 100);
    title.setStyle(sf::Text::Bold);
    window.draw(title);
    
    // Кнопка "Новая игра"
    sf::RectangleShape newGameBtn(sf::Vector2f(200, 50));
    newGameBtn.setPosition(200, 300);
    newGameBtn.setFillColor(sf::Color(100, 150, 200));
    newGameBtn.setOutlineThickness(2);
    newGameBtn.setOutlineColor(sf::Color::Black);
    window.draw(newGameBtn);
    
    sf::Text newGameText("Новая игра", font, 24);
    newGameText.setFillColor(sf::Color::White);
    newGameText.setPosition(235, 310);
    window.draw(newGameText);
    
    // Кнопка "Загрузить игру"
    sf::RectangleShape loadBtn(sf::Vector2f(200, 50));
    loadBtn.setPosition(200, 370);
    loadBtn.setFillColor(sf::Color(100, 150, 200));
    loadBtn.setOutlineThickness(2);
    loadBtn.setOutlineColor(sf::Color::Black);
    window.draw(loadBtn);
    
    sf::Text loadText("Загрузить игру", font, 24);
    loadText.setFillColor(sf::Color::White);
    loadText.setPosition(210, 380);
    window.draw(loadText);
    
    // Кнопка "Выход"
    sf::RectangleShape exitBtn(sf::Vector2f(200, 50));
    exitBtn.setPosition(200, 440);
    exitBtn.setFillColor(sf::Color(200, 100, 100));
    exitBtn.setOutlineThickness(2);
    exitBtn.setOutlineColor(sf::Color::Black);
    window.draw(exitBtn);
    
    sf::Text exitText("Выход", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(265, 450);
    window.draw(exitText);
}

void TicTacToeGUI::drawNameInput() {
    window.clear(sf::Color(240, 240, 240));
    
    sf::Text prompt("Введите имена игроков:", font, 28);
    prompt.setFillColor(sf::Color::Black);
    prompt.setPosition(150, 200);
    window.draw(prompt);
    
    sf::Text p1Label("Игрок 1 (X):", font, 24);
    p1Label.setFillColor(sf::Color::Black);
    p1Label.setPosition(150, 280);
    window.draw(p1Label);
    
    sf::RectangleShape p1Box(sf::Vector2f(300, 40));
    p1Box.setPosition(150, 320);
    p1Box.setFillColor(currentNameInput == 0 ? sf::Color::Yellow : sf::Color::White);
    p1Box.setOutlineThickness(2);
    p1Box.setOutlineColor(sf::Color::Black);
    window.draw(p1Box);
    
    sf::Text p1Text(player1Name, font, 24);
    p1Text.setFillColor(sf::Color::Black);
    p1Text.setPosition(160, 325);
    window.draw(p1Text);
    
    sf::Text p2Label("Игрок 2 (O):", font, 24);
    p2Label.setFillColor(sf::Color::Black);
    p2Label.setPosition(150, 400);
    window.draw(p2Label);
    
    sf::RectangleShape p2Box(sf::Vector2f(300, 40));
    p2Box.setPosition(150, 440);
    p2Box.setFillColor(currentNameInput == 1 ? sf::Color::Yellow : sf::Color::White);
    p2Box.setOutlineThickness(2);
    p2Box.setOutlineColor(sf::Color::Black);
    window.draw(p2Box);
    
    sf::Text p2Text(player2Name, font, 24);
    p2Text.setFillColor(sf::Color::Black);
    p2Text.setPosition(160, 445);
    window.draw(p2Text);
    
    sf::Text hint("Нажмите Enter для продолжения, ESC для отмены", font, 18);
    hint.setFillColor(sf::Color::Gray);
    hint.setPosition(100, 550);
    window.draw(hint);
}

void TicTacToeGUI::drawBoard() {
    // Рисуем сетку доски
    for (int i = 0; i <= 3; i++) {
        // Вертикальные линии
        sf::RectangleShape line(sf::Vector2f(2, BOARD_SIZE));
        line.setPosition(BOARD_OFFSET_X + i * CELL_SIZE, BOARD_OFFSET_Y);
        line.setFillColor(sf::Color::Black);
        window.draw(line);
        
        // Горизонтальные линии
        sf::RectangleShape hLine(sf::Vector2f(BOARD_SIZE, 2));
        hLine.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y + i * CELL_SIZE);
        hLine.setFillColor(sf::Color::Black);
        window.draw(hLine);
    }
    
    // Рисуем символы на доске
    Board& board = game.getBoard();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            CellState cell = board.getCell(i, j);
            int x = BOARD_OFFSET_X + j * CELL_SIZE + CELL_SIZE / 2;
            int y = BOARD_OFFSET_Y + i * CELL_SIZE + CELL_SIZE / 2;
            
            if (cell == CellState::X) {
                sf::Text xSymbol("X", font, 80);
                xSymbol.setFillColor(sf::Color::Red);
                xSymbol.setPosition(x - 25, y - 40);
                xSymbol.setStyle(sf::Text::Bold);
                window.draw(xSymbol);
            } else if (cell == CellState::O) {
                sf::CircleShape circle(40);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineThickness(5);
                circle.setOutlineColor(sf::Color::Blue);
                circle.setPosition(x - 40, y - 40);
                window.draw(circle);
            }
        }
    }
}

void TicTacToeGUI::drawGame() {
    window.clear(sf::Color(255, 255, 240));
    
    // Заголовок с текущим игроком
    std::string statusText;
    if (game.getState() == GameState::PLAYING) {
        Player* current = game.getCurrentPlayer();
        statusText = "Ход игрока: " + current->getName();
    } else if (game.getState() == GameState::GAME_OVER) {
        if (game.getIsDraw()) {
            statusText = "НИЧЬЯ!";
        } else {
            Player* winner = (game.getWinner() == CellState::X) ? 
                            game.getPlayer1() : game.getPlayer2();
            statusText = "Победитель: " + winner->getName() + "!";
        }
    }
    
    sf::Text status(statusText, font, 28);
    status.setFillColor(sf::Color::Black);
    status.setPosition(50, 50);
    status.setStyle(sf::Text::Bold);
    window.draw(status);
    
    // Информация об игроках
    Player* p1 = game.getPlayer1();
    Player* p2 = game.getPlayer2();
    
    std::string p1Info = p1->getName() + " (X): " + std::to_string(p1->getWins()) + " побед";
    std::string p2Info = p2->getName() + " (O): " + std::to_string(p2->getWins()) + " побед";
    
    sf::Text info1(p1Info, font, 20);
    info1.setFillColor(sf::Color::Black);
    info1.setPosition(50, 100);
    window.draw(info1);
    
    sf::Text info2(p2Info, font, 20);
    info2.setFillColor(sf::Color::Black);
    info2.setPosition(320, 100);
    window.draw(info2);
    
    // Рисуем доску
    drawBoard();
    
    // Подсказки
    sf::Text hint1("ESC - вернуться в меню / сохранить игру", font, 16);
    hint1.setFillColor(sf::Color::Gray);
    hint1.setPosition(50, 620);
    window.draw(hint1);
    
    if (game.getState() == GameState::GAME_OVER) {
        sf::Text hint2("R - новая игра", font, 16);
        hint2.setFillColor(sf::Color::Gray);
        hint2.setPosition(350, 620);
        window.draw(hint2);
    }
}

void TicTacToeGUI::drawGameOver() {
    // Уже реализовано в drawGame()
}

void TicTacToeGUI::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (isNameInputActive) {
                handleNameInput(event);
            } else if (isMenuActive) {
                handleMenuInput(event);
            } else {
                handleGameInput(event);
            }
        }
        
        // Отрисовка
        if (isNameInputActive) {
            drawNameInput();
        } else if (isMenuActive) {
            drawMenu();
        } else {
            drawGame();
        }
        
        window.display();
    }
}

int main() {
    try {
        TicTacToeGUI gui;
        gui.run();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

