#ifndef DATAVISUALIZER_VERTEX_HEADER
#define DATAVISUALIZER_VERTEX_HEADER
#include <glm/glm.hpp>
namespace DataVisualizer {
struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;
};
}

#endif
