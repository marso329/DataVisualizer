#ifndef DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#define DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#include "Renderer.h"
#include "Constants.h"
#include <atomic>
#include <thread>
#include <boost/thread/thread.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <thread>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DataVisualizer {
class RendererVulkanGLFW: public Renderer {
public:
	RendererVulkanGLFW();
	~RendererVulkanGLFW();
	void run();
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanUp();
protected:
private:
	GLFWwindow* window;
	boost::thread* mainthread;
	std::atomic<bool> kill;

};
extern "C" Renderer* create_Vulkan_GLFW() {
	return new RendererVulkanGLFW;
}

extern "C" void destroy_Vulkan_GLFW(Renderer* p) {
	delete p;
}
}
#endif
