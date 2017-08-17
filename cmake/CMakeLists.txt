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

#Remove render files
list(REMOVE_ITEM SOURCES *.cpp)
message(STATUS ${SOURCES})

#Add library
add_library(DataVisualizer SHARED ${SOURCES})

#link against libraries
target_link_libraries(DataVisualizer  ${MAIN_LINK_LIBS} )

#Potentially install
install(TARGETS DataVisualizer DESTINATION //usr/local/share/DataVisualizer)

#-------------------------------------------------------------------
#OpenGl-glut renderer build

file(GLOB SOURCESOPENGL "../src/renders/Renderer_OpenGL_GLUT.cpp" )

add_library(RendererOpenGLGLUT SHARED ${SOURCESOPENGL})

target_link_libraries(RendererOpenGLGLUT  ${MAIN_LINK_LIBS} -lglut )
install(TARGETS RendererOpenGLGLUT DESTINATION //usr/local/share/DataVisualizer)

#-------------------------------------------------------------------
#Vulkan-glfw renderer build

#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW3 REQUIRED --static glfw3)
#message(STATUS ${GLFW3_LIBRARIES})

file(GLOB SOURCEVULKANGLFW "../src/renders/Renderer_Vulkan_GLFW.cpp" )

add_library(RendererVulkanGLFW SHARED ${SOURCEVULKANGLFW})

target_link_libraries(RendererVulkanGLFW  ${MAIN_LINK_LIBS} -L/usr/local/lib -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXxf86vm -lXext -lXcursor -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lXdmcp -lvulkan )

