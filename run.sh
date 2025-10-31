#!/bin/bash

echo "===================================="
echo "     Tic-Tac-Toe - Запуск"
echo "===================================="
echo ""

# Поиск исполняемого файла
EXE_PATH=""

if [ -f "build/TicTacToe" ]; then
    EXE_PATH="build/TicTacToe"
elif [ -f "build/tictactoe" ]; then
    EXE_PATH="build/tictactoe"
elif [ -f "tictactoe" ]; then
    EXE_PATH="tictactoe"
elif [ -f "./build/Release/TicTacToe" ]; then
    EXE_PATH="./build/Release/TicTacToe"
elif [ -f "./build/Debug/TicTacToe" ]; then
    EXE_PATH="./build/Debug/TicTacToe"
fi

if [ -z "$EXE_PATH" ]; then
    echo "[ОШИБКА] Исполняемый файл не найден!"
    echo ""
    echo "Выполните ./build_and_run.sh для сборки проекта"
    echo ""
    exit 1
fi

echo "Запуск: $EXE_PATH"
echo ""

./$EXE_PATH

