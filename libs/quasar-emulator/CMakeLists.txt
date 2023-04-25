cmake_minimum_required(VERSION 3.15)

project(QuaSAR-Emulator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Core
    Quick
    Network
    Location
    Positioning
    QuickControls2
)

include_directories(src/cpp)

file(GLOB_RECURSE CPP_SOURCES
    src/cpp/telemetry/*
)

set(PROJECT_SOURCES
    src/cpp/main.c++

    src/qml/qml.qrc
    resources/resources.qrc
    #${SRCS} resources/appiconwin32.rc
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Location
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

message("QuaSAR-Emulator compiled successfully")
