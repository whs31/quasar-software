cmake_minimum_required(VERSION 3.16)
project(plugin VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Widgets)

qt_add_plugin(plugin)
target_sources(plugin PRIVATE
    plugin.h
    pluginDataTypes.h
    pluginHead.cpp pluginHead.h
    pluginHostAPI.cpp pluginHostAPI.h
    pluginInterface.h
)
target_compile_definitions(plugin PRIVATE
    MAKE_PLUGIN_LIB
    QT_DEPRECATED_WARNINGS
)

target_link_libraries(plugin PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(plugin PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS plugin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
