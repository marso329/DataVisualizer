#ifndef DATAVISUALIZER_DATASETS_HEADER
#define DATAVISUALIZER_DATASETS_HEADER
#include <vector>
#include "DataSet.h"
namespace DataVisualizer{
template <typename T>
class DataSets{
public:
	DataSets(){};
	void insert(const std::vector<T>& data){
		_datasets.push_back(new DataSet<T>(data));
	}
	DataSet<T>& operator[] (const int index){
		return *_datasets[index];
	}
protected:
private:
	std::vector<DataSet<T>*> _datasets;
};


}

#endif
