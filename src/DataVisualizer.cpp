#include "DataVisualizer.h"

namespace DataVisualizer{
DataVisualizer::DataVisualizer():_renderer(NULL),_columns(0),_rows(0){

}

DataVisualizer::~DataVisualizer(){
	if(_renderer!=NULL){
		_renderer->del();
	}
}

bool DataVisualizer::init(){
	//first try to load OpenGL
	return init_opengl();
}
bool DataVisualizer::init_opengl(){
	void* rendererOpenGLLib = dlopen("../lib/libRendererOpenGLGLUT.so", RTLD_LAZY);
	if(!rendererOpenGLLib){
		return false;
	}
	else{
		dlerror();
		create_t* create_renderer = (create_t*) dlsym(rendererOpenGLLib, "create_OpenGL_GLUT");
		const char* dlsym_error = dlerror();
		if (dlsym_error) {
			return false;
		}
		destroy_t* destroy_renderer = (destroy_t*) dlsym(rendererOpenGLLib, "destroy_OpenGL_GLUT");
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
