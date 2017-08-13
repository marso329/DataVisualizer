#include main library
include(../config.cmake)

#Build the main library
project (DataVisualizer)

#Build a release for now
set(CMAKE_BUILD_TYPE Release)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

#Add all source files
file(GLOB SOURCES "../src/*.cpp" "../src/*.c")

#Add library
add_library(DataVisualizer SHARED ${SOURCES})

#link against libraries
target_link_libraries(DataVisualizer  ${MAIN_LINK_LIBS} )

#Potentially install
install(TARGETS DataVisualizer DESTINATION //usr/local/share/DataVisualizer)