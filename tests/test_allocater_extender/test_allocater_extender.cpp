#include "DataVisualizer.h"
#include <vector>
#include <random>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <memory>
//#include "DataSet.h"

namespace DV= DataVisualizer;
int main(){
	DV::DataVisualizer* VC=new DV::DataVisualizer();
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(1, 2);
	if(VC->init()){
		std::cout<<"Init successful"<<std::endl;
	}
	else{
		std::cout<<"Init failed"<<std::endl;
		return 1;
	}
	float* data=(float*)malloc(256*sizeof(float));
	for(int i=0;i<256;i++){
		data[i]=dis(gen);
	}
	DV::Basic2DLinePlot<float>* plot=new DV::Basic2DLinePlot<float>(data,256);
	(*plot)[0][756]=123.0;
	std::shared_ptr<float> ptr= (*plot)[0].get_pointer();
	assert(*(ptr.get()+756)==123.0);
	free(data);
	delete plot;
	delete VC;
}
