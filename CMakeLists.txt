# 指定版本和项目
cmake_minimum_required(VERSION 3.29.2)
project(demo)

# 开启自动编译
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 匹配文件
file(GLOB SOURCE_FILE ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB RESOURCE_FILE ${PROJECT_SOURCE_DIR}/src/*.qrc)

# 链接可执行文件
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILE} ${RESOURCE_FILE})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# Qt_PATH 为 Qt 的安装地址
set(QT_PATH "C:\\Qt\\Qt5.12.0\\5.12.0\\mingw73_64")
set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)
# set(RESOURCES /src/*.qrc)
# qt5_add_resources(RESOURCES_CPP ${RESOURCES})