cmake_minimum_required(VERSION 3.10)
project(GetHardware)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include header files
include_directories(include)

# Add the main file and link components
add_executable(GetHardware src/main.cpp)
target_link_libraries(GetHardware)

# Set user's folders and files
set(src/Models/*.cpp,
    src/Collectors/*.cpp
    )