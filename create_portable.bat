@echo off
chcp 65001 >nul
echo ====================================
echo   Создание портативной версии
echo ====================================
echo.

REM Проверка наличия компилятора
where g++ >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ОШИБКА] Компилятор g++ не найден!
    pause
    exit /b 1
)

echo [ШАГ 1] Создание директории portable...
if exist "portable" rmdir /s /q portable
mkdir portable

echo [ШАГ 2] Компиляция статически связанного исполняемого файла...
g++ -std=c++17 -O2 -static main.cpp Board.cpp Player.cpp Game.cpp ^
    -o portable\tictactoe.exe ^
    -lsfml-graphics-s -lsfml-window-s -lsfml-system-s ^
    -static-libgcc -static-libstdc++ -mwindows

if %ERRORLEVEL% NEQ 0 (
    echo [ОШИБКА] Ошибка компиляции портативной версии
    echo Попытка обычной сборки...
    g++ -std=c++17 -O2 main.cpp Board.cpp Player.cpp Game.cpp ^
        -o portable\tictactoe.exe ^
        -lsfml-graphics -lsfml-window -lsfml-system ^
        -static-libgcc -static-libstdc++
    
    if %ERRORLEVEL% NEQ 0 (
        echo [ОШИБКА] Ошибка сборки
        pause
        exit /b 1
    )
    
    echo [ПРЕДУПРЕЖДЕНИЕ] Создана версия с динамическими библиотеками
    echo Скопируйте DLL файлы SFML в директорию portable
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

