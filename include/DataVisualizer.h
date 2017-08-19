#ifndef DATAVISUALIZER_DATAVISUALIZER_HEADER
#define DATAVISUALIZER_DATAVISUALIZER_HEADER
#include "Basic2DLinePlot.h"
#include "Renderer.h"
#include "Plot.h"
#include <memory>
#include <vector>

#include <dlfcn.h>
namespace DataVisualizer {
enum RE { OpenGL, Vulkan };
class DataVisualizer {
public:
	DataVisualizer();
	~DataVisualizer();
	bool init(const RE&);
	template <typename T>
	void insert_plot(Plot<T>* plot){

	}
protected:
private:
	Renderer* _renderer;
	bool init_opengl();
	bool init_vulkan();
	//std::unique_ptr<Plot*> test;
	//std::vector<std::vector<std::unique_ptr<Plot>>> _plots;
	std::size_t _columns;
	std::size_t _rows;
};
}
#endif
