#ifndef DATAVISUALIZER_RENDEREROPENGL_HEADER
#define DATAVISUALIZER_RENDEREROPENGL_HEADER
#include "Renderer.h"
namespace DataVisualizer {
	class RendererOpenGL:public Renderer{
	public:
		RendererOpenGL();
		~RendererOpenGL();
	protected:
	private:

	};
	extern "C" Renderer* create() {
	    return new RendererOpenGL;
	}

	extern "C" void destroy(Renderer* p) {
	    delete p;
	}
}
#endif
