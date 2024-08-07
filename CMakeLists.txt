cmake_minimum_required(VERSION 3.14)
project(DANA)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include_directories(
  ./include
  ./include/sinks
)

add_executable(
  T_Run
  ./tests/T_Run.cc
  ./libs/FileScheduler.cpp
  ./libs/FileScraper.cpp
  ./libs/Logger.cpp
  ./libs/Sink.cpp
  ./libs/SinkHandle.cpp
)

target_link_libraries(
  T_Run  
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(
  T_Run
)