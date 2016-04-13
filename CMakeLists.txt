cmake_minimum_required(VERSION 3.3)
project(framenet_en)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(src src/rapidxml)

set(SOURCE_FILES testframe.cpp src/frames.cpp src/builder.cpp)

add_executable(framenet_en ${SOURCE_FILES})
find_package(Boost REQUIRED COMPONENTS regex)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(framenet_en ${Boost_LIBRARIES})
endif()

add_executable(rapidtest main.cpp)
