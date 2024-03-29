cmake_minimum_required(VERSION 3.27)
project(DataStructureClassDesign)

set(CMAKE_CXX_STANDARD 11)

# 开启QT用于预处理的组件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置cmake模块的查询目录
set(CMAKE_PREFIX_PATH "D:/installation_package/Qt/6.5.3/mingw_64")

# 查找QT的模块
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# 添加源文件
add_executable(DataStructureClassDesign
        Src/Algorithm/sortAlgorithm.cpp
        Src/Algorithm/hashAlgorithm.cpp

        Src/Forms/SortWidget.ui
        Src/Forms/HashWidget.ui

        Src/Headers/SortWidget.h
        Src/Headers/HashWidget.h

        Src/Post/SortWidget.cpp
        Src/Post/HashWidget.cpp

        Src/Test/TestSort.cpp
        Src/Test/TestHash.cpp

        Src/main.cpp
)

# 添加模块
target_link_libraries(DataStructureClassDesign
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
include_directories(
        ${PROJECT_SOURCE_DIR}/Src/Headers
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
