cmake_minimum_required (VERSION 2.6)
project (functions)


# std threads
find_package(Threads REQUIRED)


# include src
include_directories("${PROJECT_SOURCE_DIR}/")


# build core library
set(CORE_LIBRARY_NAME "functions")
add_subdirectory(source)


#build executable
add_subdirectory(bin)


#build tests
add_subdirectory(tests)
