#ifndef DATAVISUALIZER_PLOT_HEADER
#define DATAVISUALIZER_PLOT_HEADER
#include "DataSets.h"
#include <type_traits>

namespace DataVisualizer {

template<typename T>
class Plot {
	static_assert((std::is_integral<T>::value||std::is_floating_point<T>::value)&&!std::is_same<T, bool>::value, "T must inherit from list");
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
