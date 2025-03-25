cmake_minimum_required(VERSION 3.16)
project(museum_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

set(CMAKE_AUTOMOC ON)  # Добавлено для автоматической обработки MOC

add_executable(museum_app main.cpp DatabaseManager.cpp MainWindow.cpp)
target_link_libraries(museum_app Qt6::Widgets Qt6::Sql)

