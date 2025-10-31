#!/bin/bash

echo "===================================="
echo "  Tic-Tac-Toe - Сборка и запуск"
echo "===================================="
echo ""

# Проверка наличия компилятора
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "[ОШИБКА] Компилятор C++ не найден!"
    echo "Установите g++ или clang++"
    exit 1
fi

# Определение компилятора
if command -v g++ &> /dev/null; then
    CXX=g++
else
    CXX=clang++
fi

echo "[ПРОВЕРКА] Используется компилятор: $CXX"

# Проверка наличия SFML
if ! pkg-config --exists sfml-all 2>/dev/null; then
    echo "[ПРЕДУПРЕЖДЕНИЕ] SFML может быть не установлена"
    echo "Установите: sudo apt-get install libsfml-dev (Ubuntu/Debian)"
    echo "            brew install sfml (macOS)"
    echo ""
fi

# Создание директории сборки
mkdir -p build
cd build

# Попытка сборки с CMake
if command -v cmake &> /dev/null; then
    echo "[ШАГ 1] Генерация проекта CMake..."
    cmake .. > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo "[ШАГ 2] Сборка проекта..."
        cmake --build . -j$(nproc 2>/dev/null || echo 4)
        
        if [ $? -eq 0 ]; then
            cd ..
            EXE_PATH=""
            
            if [ -f "build/TicTacToe" ]; then
                EXE_PATH="build/TicTacToe"
            elif [ -f "build/tictactoe" ]; then
                EXE_PATH="build/tictactoe"
            fi
            
            if [ -n "$EXE_PATH" ]; then
                echo ""
                echo "[УСПЕХ] Проект собран!"
                echo "Запуск игры..."
                echo ""
                ./$EXE_PATH
                exit 0
            fi
        fi
    fi
    
    cd ..
fi

# Прямая компиляция
echo "[ШАГ 1] Прямая компиляция..."
$CXX -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp -o tictactoe \
    $(pkg-config --cflags --libs sfml-graphics sfml-window sfml-system 2>/dev/null || \
      echo "-lsfml-graphics -lsfml-window -lsfml-system") \
    2>build_errors.txt

if [ $? -ne 0 ]; then
    echo "[ОШИБКА] Ошибка компиляции. Проверьте build_errors.txt"
    cat build_errors.txt
    rm -f build_errors.txt
    exit 1
fi

rm -f build_errors.txt

echo ""
echo "[УСПЕХ] Проект собран!"
echo "Запуск игры..."
echo ""

./tictactoe

