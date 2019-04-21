cmake_minimum_required(VERSION 2.8.13)

project(CurrencyConverter)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 REQUIRED Widgets Network)

set(PROJECT_SOURCES "main.cpp" "mainwindow.cpp" "currencyusdrates.cpp")
set(PROJECT_HEADERS "mainwindow.h" "currencyusdrates.h")
set(PROJECT_FORMS "mainwindow.ui")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_FORMS})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Network)
