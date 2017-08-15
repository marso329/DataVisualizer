#ifndef DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#define DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#include "Renderer.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DataVisualizer {
class RendererVulkanGLFW: public Renderer {
public:
	RendererVulkanGLFW();
	~RendererVulkanGLFW();
protected:
private:

};
extern "C" Renderer* create_Vulkan_GLFW() {
	return new RendererVulkanGLFW;
}

extern "C" void destroy_Vulkan_GLWF(Renderer* p) {
	delete p;
}
}
#endif
