# Makefile для Tic-Tac-Toe

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Исходные файлы
SOURCES = main.cpp Board.cpp Player.cpp Game.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = tictactoe

# Windows
ifeq ($(OS),Windows_NT)
    TARGET = tictactoe.exe
    LIBS += -static-libgcc -static-libstdc++
endif

# Правила сборки
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f savegame.txt savegame.txt_board.dat

# Пересборка
rebuild: clean all

.PHONY: all clean rebuild


