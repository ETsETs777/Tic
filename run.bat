@echo off
chcp 65001 >nul
echo ====================================
echo      Tic-Tac-Toe - Запуск
echo ====================================
echo.

REM Поиск исполняемого файла
if exist "build\Release\TicTacToe.exe" (
    echo Запуск из build\Release\...
    build\Release\TicTacToe.exe
    goto end
)

if exist "build\Debug\TicTacToe.exe" (
    echo Запуск из build\Debug\...
    build\Debug\TicTacToe.exe
    goto end
)

if exist "build\TicTacToe.exe" (
    echo Запуск из build\...
    build\TicTacToe.exe
    goto end
)

if exist "tictactoe.exe" (
    echo Запуск tictactoe.exe...
    tictactoe.exe
    goto end
)

echo [ОШИБКА] Исполняемый файл не найден!
echo.
echo Выполните build_and_run.bat для сборки проекта
echo.
pause
exit /b 1

:end
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Игра завершена с ошибкой
    pause
)

