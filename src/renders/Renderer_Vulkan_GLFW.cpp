#include "Renderer_Vulkan_GLFW.h"
namespace DataVisualizer {
RendererVulkanGLFW::RendererVulkanGLFW() :
		window(NULL), mainthread(NULL), kill(false) {
	run();
}

RendererVulkanGLFW::~RendererVulkanGLFW() {
	kill = true;
	mainthread->join();
	cleanUp();
}

void RendererVulkanGLFW::run() {
	initWindow();
	initVulkan();
	mainthread = new boost::thread(&RendererVulkanGLFW::mainLoop, this);

}

void RendererVulkanGLFW::initVulkan() {

}
void RendererVulkanGLFW::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

}

void RendererVulkanGLFW::mainLoop() {
	  while (!glfwWindowShouldClose(window)) {
	     glfwPollEvents();

	  }}

void RendererVulkanGLFW::cleanUp() {
	glfwDestroyWindow (window);

	glfwTerminate();
}
}
