#ifndef DATAVISUALIZER_PLOT_HEADER
#define DATAVISUALIZER_PLOT_HEADER
#include "DataSets.h"

namespace DataVisualizer {

template<typename T>
class Plot {
public:
	explicit Plot():_datasets(new DataSets<T>()) {
	};
	explicit Plot(const std::vector<T>& data):Plot(){
		_datasets->insert(data);
	}
	explicit Plot(T* data,std::size_t size):Plot(){
		_datasets->insert(data,size);
	}
	~Plot(){
		delete _datasets;
	}

	DataSet<T>& operator[] (const int index){
		return (*_datasets)[index];
	}
protected:
private:
	DataSets<T>* _datasets;
};

}

#endif
