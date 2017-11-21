cmake_minimum_required(VERSION 3.0)
project(CMPE142_Sleeping_TA)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)

add_executable(CMPE142F17Group4 ${SOURCE_FILES})
target_link_libraries(CMPE142F17Group4 ${CMAKE_THREAD_LIBS_INIT})