#ifndef DATAVISUALIZER_DATAVISUALIZER_HEADER
#define DATAVISUALIZER_DATAVISUALIZER_HEADER
#include "Basic2DLinePlot.h"
#include "Renderer.h"

#include <dlfcn.h>
namespace DataVisualizer {
class DataVisualizer {
public:
	DataVisualizer();
	bool init();
protected:
private:
	Renderer* _renderer;
};
}
#endif
