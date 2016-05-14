cmake_minimum_required (VERSION 2.6)
project (PD)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -lpthread")

find_package( Threads )


FILE(GLOB srcs src/*.cpp)

add_executable(PD ${srcs})

target_link_libraries( PD ${CMAKE_THREAD_LIBS_INIT} )


