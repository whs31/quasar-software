cmake_minimum_required(VERSION 3.15)

project(updateservice LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(COMPANY "Radar-MMS")
set(COPYRIGHT "Copyright (c) 2023 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}") # For the executables

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
)

include_directories(src/c++)

set(PROJECT_SOURCES
    src/c++/main.c++
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_definitions(
    -DPROJECT_NAME="${PROJECT_NAME}"
    -DPROJECT_COMPANY="${COMPANY}"
)

message("${PROJECT_NAME} compiled successfully")
