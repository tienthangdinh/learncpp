cmake_minimum_required(VERSION 3.15)
project(RobotBatteryProject VERSION 1.0 LANGUAGES CXX)

# Force the project to use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define your executable and list all source files (.cpp)
add_executable(robot_program 
    src/main.cpp 
    src/robot_battery.cpp
)

# Tell CMake where to look for header files (.hpp)
target_include_directories(robot_program PRIVATE include)
