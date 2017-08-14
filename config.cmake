cmake_minimum_required (VERSION 3.5.1)

#Macro for all subdirs
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

#Main library links
set ( MAIN_LINK_LIBS -lboost_system )

#Link against the main library and other libraries
set ( PROJECT_LINK_LIBS DataVisualizer.so ${MAIN_LINK_LIBS} )

#library folder to link against
link_directories( ${CMAKE_SOURCE_DIR}/lib )

#Where to put library files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#include folder
include_directories(${CMAKE_SOURCE_DIR}/include)

#c++ flags, this should be in a global file
set (CMAKE_CXX_FLAGS "-std=c++11 -g -Werror -Wall -Wextra -pedantic-errors")

