cmake_minimum_required (VERSION 3.15)

project(LPVL)

set(LPVL_COMPILE_TO_STATIC TRUE)
set(LPVL_TESTS_ENABLED FALSE)
set(LPVL_REMOVE_QT_RELATED_FUNCTIONS FALSE)

if(NOT ${LPVL_REMOVE_QT_RELATED_FUNCTIONS})
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Positioning)
endif()

if(${LPVL_TESTS_ENABLED})
    find_package(GTest)
endif()

include_directories(src, include)

set (LPVL_CORE
    src/global/lpvlglobal.h
)

set (LPVL_CORE_INCLUDE
    include/LPVL/global
)

set (SRC
    ${LPVL_CORE} ${LPVL_CORE_INCLUDE}
)

if(${LPVL_COMPILE_TO_STATIC})
    add_library(${PROJECT_NAME}
        ${SRC}
    )

    target_compile_definitions (${PROJECT_NAME} PRIVATE LPVL_LIBRARY LPVL_STATIC)
else()
    add_library(${PROJECT_NAME} SHARED
        ${SRC}
    )

    target_compile_definitions (${PROJECT_NAME} PRIVATE LPVL_LIBRARY)
endif ()

if (NOT ${CSS_REMOVE_QT_RELATED_FUNCTIONS})
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Positioning
    )
endif()

if(${LPVL_TESTS_ENABLED})
    set(TESTS
        ${SRC}
    )

    add_executable(test_lpvl ${TESTS})

    target_link_libraries(test_lpvl
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Positioning
        GTest::GTest
    )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)

set_target_properties (${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "css"
    PREFIX ""
)
