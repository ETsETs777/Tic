@echo off
chcp 65001 >nul
echo ====================================
echo   Tic-Tac-Toe - Сборка и запуск
echo ====================================
echo.

REM Проверка наличия компилятора
set COMPILER=
set COMPILER_TYPE=

REM Проверка g++ (MinGW)
where g++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set COMPILER=g++
    set COMPILER_TYPE=mingw
    echo [НАЙДЕН] Компилятор: g++ (MinGW)
    goto compiler_found
)

REM Проверка cl.exe (Visual Studio)
where cl >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set COMPILER=cl
    set COMPILER_TYPE=msvc
    echo [НАЙДЕН] Компилятор: cl.exe (Visual Studio)
    goto compiler_found
)

REM Проверка clang++ (LLVM)
where clang++ >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    set COMPILER=clang++
    set COMPILER_TYPE=clang
    echo [НАЙДЕН] Компилятор: clang++ (LLVM)
    goto compiler_found
)

REM Компилятор не найден
echo.
echo ═══════════════════════════════════════════════════════════════
echo   [ОШИБКА] Компилятор C++ не найден!
echo ═══════════════════════════════════════════════════════════════
echo.
echo Для сборки проекта необходим один из следующих компиляторов:
echo.
echo   1. MinGW-w64 (рекомендуется для начинающих)
echo      Скачать: https://www.mingw-w64.org/downloads/
echo      Или установить через MSYS2: https://www.msys2.org/
echo.
echo   2. Visual Studio (с компонентом C++)
echo      Скачать: https://visualstudio.microsoft.com/downloads/
echo      Установите "Desktop development with C++"
echo.
echo   3. LLVM/Clang
echo      Скачать: https://releases.llvm.org/download.html
echo.
echo ═══════════════════════════════════════════════════════════════
echo.
echo Альтернатива: Используйте CMake + Visual Studio (если установлен)
echo.
pause
exit /b 1

:compiler_found

REM Проверка наличия SFML
echo [ПРОВЕРКА] Поиск библиотеки SFML...
if not exist "C:\SFML" (
    echo [ПРЕДУПРЕЖДЕНИЕ] SFML не найдена в стандартном пути
    echo Пожалуйста, убедитесь, что SFML установлена и доступна
    echo.
)

REM Создание директории сборки
if not exist "build" mkdir build
cd build

REM Генерация проекта CMake
where cmake >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo [ШАГ 1] Генерация проекта CMake...
    cmake .. >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        echo [ШАГ 2] Сборка проекта...
        cmake --build . --config Release
        if %ERRORLEVEL% EQU 0 (
            goto find_exe
        )
    )
    echo [ИНФО] CMake сборка не удалась, пробуем прямую компиляцию...
    cd ..
) else (
    echo [ИНФО] CMake не найден, используется прямая компиляция...
    cd ..
)
goto direct_build

:find_exe
REM Поиск исполняемого файла после CMake
if exist "Release\TicTacToe.exe" (
    set EXE_PATH=Release\TicTacToe.exe
) else if exist "TicTacToe.exe" (
    set EXE_PATH=TicTacToe.exe
) else if exist "Debug\TicTacToe.exe" (
    set EXE_PATH=Debug\TicTacToe.exe
) else (
    echo [ОШИБКА] Исполняемый файл не найден после сборки
    pause
    exit /b 1
)

cd ..
echo.
echo [УСПЕХ] Проект собран через CMake!
echo Запуск игры...
echo.
%CD%\build\%EXE_PATH%
goto end

:direct_build
echo [ШАГ 1] Прямая компиляция с %COMPILER%...
echo.

if "%COMPILER_TYPE%"=="mingw" (
    %COMPILER% -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp -o tictactoe.exe -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ 2>build_errors.txt
) else if "%COMPILER_TYPE%"=="clang" (
    %COMPILER% -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp -o tictactoe.exe -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++ 2>build_errors.txt
) else if "%COMPILER_TYPE%"=="msvc" (
    echo [ОШИБКА] Visual Studio требует специальную настройку
    echo Используйте CMake для Visual Studio:
    echo   mkdir build ^&^& cd build
    echo   cmake .. -G "Visual Studio 16 2019"
    echo   cmake --build . --config Release
    pause
    exit /b 1
) else (
    echo [ОШИБКА] Неизвестный тип компилятора
    pause
    exit /b 1
)

if %ERRORLEVEL% NEQ 0 (
    echo [ОШИБКА] Ошибка компиляции!
    echo.
    if exist build_errors.txt (
        echo Содержимое лога ошибок:
        echo ────────────────────────────────────────────────────────────
        type build_errors.txt
        echo ────────────────────────────────────────────────────────────
        echo.
    )
    echo Возможные причины:
    echo   1. SFML не установлена или не найдена
    echo   2. Неправильные пути к библиотекам
    echo   3. Несовместимые версии компилятора и SFML
    echo.
    echo Решение: Используйте CMake или установите SFML правильно
    echo.
    if exist build_errors.txt del build_errors.txt
    pause
    exit /b 1
)

del build_errors.txt >nul 2>&1
echo.
echo [УСПЕХ] Проект собран!
echo Запуск игры...
echo.
if exist tictactoe.exe (
    tictactoe.exe
) else (
    echo [ОШИБКА] Исполняемый файл не создан
    pause
    exit /b 1
)

:end
pause

