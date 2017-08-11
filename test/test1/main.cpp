#include "DataVisualizer.h"
#include <iostream>
#include <vector>
//#include "DataSet.h"

namespace DV= DataVisualizer;
int main(){
	DV::DataVisualizer* VC=new DV::DataVisualizer();
	if(VC->init()){
		std::cout<<"Init successful"<<std::endl;
	}
	else{
		std::cout<<"Init failed"<<std::endl;
		return 1;
	}
	std::vector<float> data={1.0, 2.0, 2.0, 4.0};
	DV::Basic2DLinePlot<float>* plot=new DV::Basic2DLinePlot<float>(data);
	for(std::size_t i=0;i<4;i++){
		std::cout<<(*plot)[0][i]<<std::endl;
	}
	std::cout<<std::endl;
}
