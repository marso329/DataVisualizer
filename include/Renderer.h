#ifndef DATAVISUALIZER_RENDERER_HEADER
#define DATAVISUALIZER_RENDERER_HEADER
#include <cstdlib>
namespace DataVisualizer {
class Renderer;
typedef Renderer* create_t();
typedef void destroy_t(Renderer*);
class Renderer {
public:
	Renderer(): destroy_renderer(NULL){

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
	virtual void wait()=0;
protected:
	destroy_t* destroy_renderer;
private:
};

}
#endif
