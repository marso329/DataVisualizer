#ifndef DATAVISUALIZER_RENDERER_HEADER
#define DATAVISUALIZER_RENDERER_HEADER
#include <cstdlib>
#include "Plot.h"
#include <vector>
#include <queue>
namespace DataVisualizer {
class Renderer;
typedef Renderer* create_t();
typedef void destroy_t(Renderer*);
class Renderer {
public:
	Renderer(): destroy_renderer(NULL),new_plot(false){

	}
	virtual ~Renderer(){};
	void set_deleter(destroy_t* deleter){
		destroy_renderer=deleter;
	};
	void del(){
		if(destroy_renderer!=NULL){
			destroy_renderer(this);
		}
	}
	template<typename T>
	void insert_plot(Plot<T>* plot) {
		_plots_queue.push(dynamic_cast<PlotBase*>(plot));
		new_plot=true;
	}

	virtual void wait()=0;
protected:
	destroy_t* destroy_renderer;
	std::queue<PlotBase*> _plots_queue;
	std::vector<PlotBase*> _plots;
	bool new_plot;
private:
};

}
#endif
