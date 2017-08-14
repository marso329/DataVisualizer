#include "DataVisualizer.h"

namespace DataVisualizer{
DataVisualizer::DataVisualizer():_renderer(NULL){

}

bool DataVisualizer::init(){
	//first try to load OpenGL
	void* rendererOpenGLLib = dlopen("../lib/libRendererOpenGL.so", RTLD_LAZY);
	if(!rendererOpenGLLib){
		return false;
	}
	else{
		dlerror();
		create_t* create_renderer = (create_t*) dlsym(rendererOpenGLLib, "create");
		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			return false;
		}
		destroy_t* destroy_renderer = (destroy_t*) dlsym(rendererOpenGLLib, "destroy");
		dlsym_error = dlerror();
		if (dlsym_error) {
			return false;
		}
		 _renderer = create_renderer();
		 _renderer->set_deleter(destroy_renderer);
	}
	return true;
}
}
