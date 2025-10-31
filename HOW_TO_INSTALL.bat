@echo off
chcp 65001 >nul
echo ====================================
echo   Инструкция по установке
echo ====================================
echo.
echo Открываю файл INSTALL_COMPILER.md...
echo.

REM Попытка открыть файл разными способами
if exist "INSTALL_COMPILER.md" (
    REM Windows 10/11
    start "" "INSTALL_COMPILER.md"
    
    REM Если не открылось, пробуем через notepad
    timeout /t 2 >nul
    if not exist "%TEMP%\install_check.txt" (
        start notepad "INSTALL_COMPILER.md"
    )
) else (
    echo [ОШИБКА] Файл INSTALL_COMPILER.md не найден!
    echo.
    echo Краткая инструкция:
    echo.
    echo 1. Установите MinGW-w64:
    echo    https://www.mingw-w64.org/downloads/
    echo    или через MSYS2: https://www.msys2.org/
    echo.
    echo 2. Установите SFML:
    echo    https://www.sfml-dev.org/download.php
    echo.
    echo 3. Добавьте компилятор в PATH
    echo.
    pause
)

