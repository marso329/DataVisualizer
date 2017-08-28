#ifndef DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#define DATAVISUALIZER_RENDERERVULKANGLFW_HEADER
#include "Renderer.h"
#include "Constants.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <array>
#include <set>
#include <atomic>

#include <boost/thread/thread.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace DataVisualizer {

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = { };
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions =
				{ };

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}
};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class RendererVulkanGLFW: public Renderer {
public:
	RendererVulkanGLFW();
	~RendererVulkanGLFW();
	void run();
	void wait();
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanUp();
	void createInstance();
	bool checkValidationLayerSupport();
	VkResult CreateDebugReportCallbackEXT(VkInstance instance,
			const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugReportCallbackEXT* pCallback);
	void DestroyDebugReportCallbackEXT(VkInstance instance,
			VkDebugReportCallbackEXT callback,
			const VkAllocationCallbacks* pAllocator);
	void recreateSwapChain();
	void cleanupSwapChain();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSemaphores();
	void drawFrame();
	void createVertexBuffer();
	void createDescriptorSetLayout();
	void createDescriptorSet();
	void updateUniformBuffer();
	void updateVertexBuffer();

	void createDepthResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
			VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
	void createTextureImage();
	void createTextureImageView();
	void createTextureSampler();
	void createImage(uint32_t width, uint32_t height, VkFormat format,
			VkImageTiling tiling, VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties, VkImage& image,
			VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format,
			VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width,
			uint32_t height);
	void createIndexBuffer();
	void createUniformBuffer();
	void createDescriptorPool();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
			VkMemoryPropertyFlags properties, VkBuffer& buffer,
			VkDeviceMemory& bufferMemory);
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkCommandBuffer beginSingleTimeCommands();
	VkImageView createImageView(VkImage image, VkFormat format,
			VkImageAspectFlags aspectFlags);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(
			const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(
			const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();

	uint32_t findMemoryType(uint32_t typeFilter,
			VkMemoryPropertyFlags properties);

	static std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t) file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType,
			uint64_t obj, size_t location, int32_t code,
			const char* layerPrefix, const char* msg, void* userData) {
		(void) flags;
		(void) objType;
		(void) obj;
		(void) location;
		(void) code;
		(void) layerPrefix;
		(void) userData;
		std::cerr << "validation layer: " << msg << std::endl;
		return VK_FALSE;
	}

	static void onWindowResized(GLFWwindow* window, int width, int height) {
		if (width == 0 || height == 0)
			return;

		RendererVulkanGLFW* app =
				reinterpret_cast<RendererVulkanGLFW*>(glfwGetWindowUserPointer(
						window));
		app->recreateSwapChain();
	}

protected:
private:
	//GLFW specific
	GLFWwindow* window;

	//Vulkan specific
	VkInstance instance;
	const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation" };

	const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	//for now
	const bool enableValidationLayers = true;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;

	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;

	 std::vector<Vertex> vertices = { { { -0.5f, -0.5f, 0.0f }, { 1.0f,
			0.0f, 0.0f }, { 1.0f, 0.0f } }, { { 0.5f, -0.5f, 0.0f }, { 0.0f,
			1.0f, 0.0f }, { 0.0f, 0.0f } }, { { 0.5f, 0.5f, 0.0f }, { 0.0f,
			0.0f, 1.0f }, { 0.0f, 1.0f } }, { { -0.5f, 0.5f, 0.0f }, { 1.0f,
			1.0f, 1.0f }, { 1.0f, 1.0f } },

	{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } }, { { 0.5f,
			-0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }, { { 0.5f,
			0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } }, { { -0.5f,
			0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } } };

	const std::vector<uint16_t> indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
	//DataVisualizer specific
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
