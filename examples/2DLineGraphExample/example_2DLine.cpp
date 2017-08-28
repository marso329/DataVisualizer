#include "DataVisualizer.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
//#include "DataSet.h"

namespace DV= DataVisualizer;
int main(){

	//creation and initialization
	DV::DataVisualizer* VC=new DV::DataVisualizer();
	assert(VC->init(DV::RE::Vulkan));
	std::vector<float> data;
	for(std::size_t i=0;i<256;i++){
		data.push_back(sin(0.024543*static_cast<double>(i)));
	}
	DV::Basic2DLinePlot<float>* plot=new DV::Basic2DLinePlot<float>(data);
	VC->insert_plot(plot);
	VC->wait_for_window_to_close();
	delete plot;
	delete VC;
}
