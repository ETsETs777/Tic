# Инструкция по установке компилятора C++

Для сборки проекта Tic-Tac-Toe необходим компилятор C++ и библиотека SFML.

## 🪟 Windows

### Вариант 1: MinGW-w64 (Рекомендуется)

**Способ 1: Через MSYS2 (рекомендуется)**

1. Скачайте и установите MSYS2: https://www.msys2.org/
2. Откройте MSYS2 terminal
3. Выполните:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make
pacman -S mingw-w64-x86_64-sfml
```
4. Добавьте `C:\msys64\mingw64\bin` в PATH

**Способ 2: Прямая установка**

1. Скачайте MinGW-w64: https://www.mingw-w64.org/downloads/
2. Или используйте готовый установщик: https://github.com/brechtsanders/winlibs_mingw/releases
3. Распакуйте в `C:\mingw64`
4. Добавьте `C:\mingw64\bin` в PATH

**Проверка установки:**
```cmd
g++ --version
```

### Вариант 2: Visual Studio

1. Скачайте Visual Studio Community: https://visualstudio.microsoft.com/downloads/
2. При установке выберите:
   - "Desktop development with C++"
   - "CMake tools for Windows"
3. После установки откройте "Developer Command Prompt for VS"
4. Перейдите в директорию проекта и используйте CMake

**Использование:**
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

### Вариант 3: LLVM/Clang

1. Скачайте LLVM: https://releases.llvm.org/download.html
2. Установите и добавьте в PATH
3. Также потребуется установить MinGW или MSVC для стандартной библиотеки

## 📚 Установка SFML

### Windows (с MinGW)

**Через MSYS2:**
```bash
pacman -S mingw-w64-x86_64-sfml
```

**Вручную:**
1. Скачайте SFML: https://www.sfml-dev.org/download.php
2. Выберите версию для MinGW
3. Распакуйте в `C:\SFML`
4. При компиляции укажите пути:
```cmd
g++ -I"C:\SFML\include" -L"C:\SFML\lib" ...
```

### Windows (с Visual Studio)

1. Скачайте SFML для Visual Studio
2. Распакуйте в `C:\SFML`
3. Используйте CMake, который автоматически найдет SFML

**Или через vcpkg (рекомендуется):**
```cmd
vcpkg install sfml
```

## 🐧 Linux

### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsfml-dev
```

### Fedora/RHEL

```bash
sudo dnf install gcc-c++ cmake SFML-devel
```

### Arch Linux

```bash
sudo pacman -S base-devel cmake sfml
```

## 🍎 macOS

```bash
# Установка Homebrew (если еще не установлен)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Установка инструментов
brew install gcc cmake sfml
```

## ✅ Проверка установки

После установки проверьте:

```bash
# Проверка компилятора
g++ --version
# или
cl

# Проверка CMake
cmake --version

# Проверка SFML (через pkg-config на Linux/macOS)
pkg-config --modversion sfml-all
```

## 🚀 Быстрый старт после установки

После установки всех зависимостей просто запустите:

**Windows:**
```cmd
build_and_run.bat
```

**Linux/macOS:**
```bash
chmod +x build_and_run.sh
./build_and_run.sh
```

## 💡 Решение проблем

### Ошибка "компилятор не найден"

1. Убедитесь, что компилятор установлен
2. Проверьте PATH:
   ```cmd
   echo %PATH%
   ```
3. Добавьте путь к компилятору в PATH через:
   - Панель управления → Система → Переменные среды
   - Или через командную строку:
     ```cmd
     set PATH=%PATH%;C:\путь\к\компилятору\bin
     ```

### Ошибка "SFML не найдена"

1. Убедитесь, что SFML установлена
2. Проверьте, что пути к библиотеке указаны правильно
3. Попробуйте использовать CMake вместо прямой компиляции

### Ошибки линковки

1. Убедитесь, что версии компилятора и SFML совместимы
2. Проверьте, что используете правильные библиотеки (Debug/Release)
3. На Windows убедитесь, что DLL файлы доступны

## 📞 Получение помощи

Если у вас возникли проблемы:
1. Проверьте файл `build_errors.txt` после неудачной сборки
2. Убедитесь, что все зависимости установлены
3. Попробуйте использовать CMake вместо прямой компиляции

