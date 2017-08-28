include(../config.cmake)
#This is the project for building all tests
project (examples)

#Where to put all binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin_examples)

#Call macro to get subdirs
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

#Remove CMakeFiles folder
list(REMOVE_ITEM SUBDIRS CMakeFiles)

#For each subdirectory
FOREACH(subdir ${SUBDIRS})
  #All files in the current subdir
  file(GLOB files ${subdir}/*)
  #same
  file(GLOB name ${subdir}/*.cpp)
  #Remove every file that does not fit example_*.cpp
  list(REMOVE_ITEM name !*example_*.cpp)
  #remove the extension from the filename
  get_filename_component(MYFILE_WITHOUT_EXT ${name} NAME_WE)
  #create a executable
  add_executable(${MYFILE_WITHOUT_EXT} ${files})
  #link executable against main library
  target_link_libraries(${MYFILE_WITHOUT_EXT} ${PROJECT_LINK_LIBS} -lboost_system )
ENDFOREACH()
