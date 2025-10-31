cmake_minimum_required(VERSION 3.12)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Исходные файлы
set(SOURCES
    main.cpp
    Board.cpp
    Player.cpp
    Game.cpp
)

set(HEADERS
    Board.h
    Player.h
    Game.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключение SFML
target_link_libraries(${PROJECT_NAME} 
    SFML::System
    SFML::Window
    SFML::Graphics
)

# Для Windows
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()


