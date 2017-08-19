#include "DataVisualizer.h"
#include <cassert>

namespace DV= DataVisualizer;
int main(){
	DV::DataVisualizer* VC=new DV::DataVisualizer();
	assert(VC->init(DV::RE::Vulkan));
	delete VC;
}
