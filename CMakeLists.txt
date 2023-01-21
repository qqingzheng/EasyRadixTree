cmake_minimum_required(VERSION 3.24.2)
project(RadixTree VERSION 1.0)

# 设定 C++ 标准为 14。
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 生成配置文件
configure_file(config.in config.h) # 配置文件生成在 PROJECT_BINARY_DIR 变量处，也就是build文件夹里面

# 添加可执行文件


# 添加链接文件夹
file(GLOB_RECURSE SRC_LIST src/*.cpp)
add_library(RadixTreeLib "${SRC_LIST}")


add_executable(test src/main.cpp)
target_link_libraries(test PUBLIC RadixTreeLib)


# 添加 include 的文件夹
target_include_directories(RadixTreeLib 
        PUBLIC "${PROJECT_BINARY_DIR}"
        PUBLIC "include/"
        )



