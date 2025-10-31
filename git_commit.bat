@echo off
chcp 65001 >nul
echo ====================================
echo   Автоматический коммит в Git
echo ====================================
echo.

REM Переход в директорию проекта
cd /d "%~dp0"

REM Проверка наличия Git
where git >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ОШИБКА] Git не найден!
    pause
    exit /b 1
)

REM Проверка наличия изменений
git status --porcelain >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ИНФО] Нет изменений для коммита
    pause
    exit /b 0
)

echo [ШАГ 1] Добавление всех изменений...
git add .

echo [ШАГ 2] Создание коммита...
if "%1"=="" (
    set COMMIT_MSG=Update: автоматическое обновление проекта
) else (
    set COMMIT_MSG=%*
)

git commit -m "%COMMIT_MSG%"
if %ERRORLEVEL% NEQ 0 (
    echo [ОШИБКА] Ошибка создания коммита
    pause
    exit /b 1
)

echo.
echo [УСПЕХ] Коммит создан!
echo.

REM Попытка отправки на GitHub
echo [ШАГ 3] Попытка отправки на GitHub...
git push origin main
if %ERRORLEVEL% EQU 0 (
    echo [УСПЕХ] Изменения отправлены на GitHub!
) else (
    echo [ПРЕДУПРЕЖДЕНИЕ] Не удалось отправить на GitHub
    echo Вы можете сделать это позже командой: git push origin main
)

echo.
pause

