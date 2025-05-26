cmake_minimum_required(VERSION 3.14)
project(Main_Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
	FetchContent_Declare(
  mettle
  GIT_REPOSITORY https://github.com/jimporter/mettle.git 
  GIT_TAG        master
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

	FetchContent_MakeAvailable(mettle)

# link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} mettle)

add_test(NAME tests COMMAND ${PROJECT_NAME})

# post build command
add_custom_command(
     TARGET ${PROJECT_NAME}  
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${PROJECT_NAME}
)