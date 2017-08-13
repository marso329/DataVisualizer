cmake_minimum_required (VERSION 3.5.1)
#For creating tests
enable_testing()
#Build main library
add_subdirectory(cmake)
#build tests
add_subdirectory(tests)
#build examples
add_subdirectory(examples)
