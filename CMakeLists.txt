cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)

#
# third party libraries
#
add_subdirectory(third_party/catch2)

#
# compile options
#
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror -O2)

#
# release/debug compile options
#
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g -O3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O3")
set(CMAKE_C_FLAGS_DEBUG "-DENABLE_DEBUG -g3 -O0 -fsanitize=address -fno-omit-frame-pointer -fno-common")
set(CMAKE_CXX_FLAGS_DEBUG "-DENABLE_DEBUG -g3 -O0 -fsanitize=address -fno-omit-frame-pointer -fno-common")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fsanitize=address")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

#
# source directory and files
#
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
FILE(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

#
# targets
#
foreach(SRC_FILE ${SRC_FILES})
    string(REPLACE ".cpp" "" targetPath "${SRC_FILE}")
    get_filename_component(targetName "${targetPath}" NAME)
    add_executable("${targetName}" "${SRC_FILE}")
    target_include_directories("${targetName}" PRIVATE ${SRC_DIR})
    target_link_libraries("${targetName}" PRIVATE Catch2::Catch2WithMain)
endforeach()
