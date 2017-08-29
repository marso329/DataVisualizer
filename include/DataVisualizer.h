#ifndef DATAVISUALIZER_DATAVISUALIZER_HEADER
#define DATAVISUALIZER_DATAVISUALIZER_HEADER
#include "Basic2DLinePlot.h"
#include "Renderer.h"
#include "Plot.h"
#include <memory>
#include <vector>

#include <dlfcn.h>
namespace DataVisualizer {
enum RE {
	OpenGL, Vulkan
};
class DataVisualizer {
public:
	DataVisualizer();
	~DataVisualizer();
	bool init(const RE&);
	void wait_for_window_to_close();
	template<typename T>
	void insert_plot(Plot<T>* plot) {
		//_plots.push_back(dynamic_cast<PlotBase*>(plot));
	if(_renderer!=NULL){
		_renderer->insert_plot(plot);
	}
	}
protected:
private:
	Renderer* _renderer;
	bool init_opengl();
	bool init_vulkan();
	//std::vector<PlotBase*> _plots;
	std::size_t _columns;
	std::size_t _rows;
}
;
}
#endif
