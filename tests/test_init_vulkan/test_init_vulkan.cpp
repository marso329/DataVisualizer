#include "DataVisualizer.h"
#include <cassert>
#include <unistd.h>
namespace DV= DataVisualizer;
int main(){
	DV::DataVisualizer* VC=new DV::DataVisualizer();
	assert(VC->init(DV::RE::Vulkan));
	usleep(10000000);
	delete VC;
}
