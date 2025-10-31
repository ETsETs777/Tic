@echo off
chcp 65001 >nul
echo ====================================
echo   Создание портативной версии
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
    echo [ПРЕДУПРЕЖДЕНИЕ] Visual Studio может потребовать дополнительные настройки
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
echo Для создания портативной версии необходим компилятор C++.
echo.
echo Для установки компилятора:
echo   1. Откройте файл INSTALL_COMPILER.md
echo   2. Или запустите HOW_TO_INSTALL.bat
echo.
echo Быстрая установка MinGW-w64 через MSYS2:
echo   1. Скачайте MSYS2: https://www.msys2.org/
echo   2. Откройте MSYS2 terminal и выполните:
echo      pacman -Syu
echo      pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-sfml
echo   3. Добавьте C:\msys64\mingw64\bin в PATH
echo.
echo ═══════════════════════════════════════════════════════════════
echo.
pause
exit /b 1

:compiler_found

echo [ШАГ 1] Создание директории portable...
if exist "portable" rmdir /s /q portable
mkdir portable

echo [ШАГ 2] Компиляция статически связанного исполняемого файла...

if "%COMPILER_TYPE%"=="mingw" (
    echo Попытка статической сборки с SFML...
    %COMPILER% -std=c++17 -O2 -static main.cpp Board.cpp Player.cpp Game.cpp ^
        -o portable\tictactoe.exe ^
        -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
        -static-libgcc -static-libstdc++ -mwindows 2>portable_build_errors.txt
    
    if %ERRORLEVEL% NEQ 0 (
        echo Попытка обычной сборки...
        %COMPILER% -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp ^
            -o portable\tictactoe.exe ^
            -lsfml-graphics -lsfml-window -lsfml-system ^
            -static-libgcc -static-libstdc++ 2>portable_build_errors.txt
        
        if %ERRORLEVEL% NEQ 0 (
            echo [ОШИБКА] Ошибка компиляции!
            if exist portable_build_errors.txt (
                echo.
                echo Лог ошибок:
                type portable_build_errors.txt
                del portable_build_errors.txt
            )
            echo.
            echo Возможные причины:
            echo   1. SFML не установлена или не найдена
            echo   2. Неправильные пути к библиотекам SFML
            echo.
            pause
            exit /b 1
        )
        
        echo [ПРЕДУПРЕЖДЕНИЕ] Создана версия с динамическими библиотеками
        echo Скопируйте DLL файлы SFML в директорию portable
    ) else (
        echo [УСПЕХ] Статическая сборка успешна!
    )
    if exist portable_build_errors.txt del portable_build_errors.txt >nul 2>&1
) else if "%COMPILER_TYPE%"=="clang" (
    %COMPILER% -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp ^
        -o portable\tictactoe.exe ^
        -lsfml-graphics -lsfml-window -lsfml-system ^
        -static-libgcc -static-libstdc++ 2>portable_build_errors.txt
    
    if %ERRORLEVEL% NEQ 0 (
        echo [ОШИБКА] Ошибка компиляции!
        if exist portable_build_errors.txt (
            type portable_build_errors.txt
            del portable_build_errors.txt
        )
        pause
        exit /b 1
    )
) else if "%COMPILER_TYPE%"=="msvc" (
    echo [ОШИБКА] Visual Studio требует специальную настройку для портативной версии
    echo Используйте CMake для сборки, затем скопируйте exe и необходимые DLL
    pause
    exit /b 1
)

REM Копирование необходимых файлов
if exist "arial.ttf" (
    copy arial.ttf portable\ >nul
    echo [ШАГ 3] Скопирован файл шрифта
)

echo.
echo [УСПЕХ] Портативная версия создана в директории portable\
echo.
echo Теперь вы можете скопировать папку portable на другой компьютер
echo и запустить tictactoe.exe без установки дополнительных библиотек
echo.
pause

