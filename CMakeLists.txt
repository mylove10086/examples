cmake_minimum_required(VERSION 3.17)
project(useCeisum)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)       #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)           #设置库文件的输出目录

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenMP)

#CCesium库的安装路径，这个时mac系统的，window系统可以看教程
#CCesium库可以到百度云地址下载
#百度云地址链接：https://pan.baidu.com/s/1pOHM5r4LiHOfl3omIViySw?pwd=i32h
#提取码：i32h
#list(APPEND CMAKE_PREFIX_PATH "D:/install") # 安装路径前缀
list(APPEND CMAKE_PREFIX_PATH "/Users/mylove/Desktop/install") # 安装路径前缀

find_package(Cesium)
include_directories(${Cesium_include_dirs})

add_subdirectory(dome)
