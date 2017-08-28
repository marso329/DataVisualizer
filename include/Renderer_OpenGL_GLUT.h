#ifndef DATAVISUALIZER_RENDEREROPENGLGLUT_HEADER
#define DATAVISUALIZER_RENDEREROPENGLGLUT_HEADER
#include "Renderer.h"
#include <GL/glut.h>
namespace DataVisualizer {
class RendererOpenGLGLUT: public Renderer {
public:
	RendererOpenGLGLUT();
	~RendererOpenGLGLUT();
	void wait();
protected:
private:

};
extern "C" Renderer* create_OpenGL_GLUT() {
	return new RendererOpenGLGLUT;
}

extern "C" void destroy_OpenGL_GLUT(Renderer* p) {
	delete p;
}
}
#endif
