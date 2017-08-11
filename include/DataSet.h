#ifndef DATAVISUALIZER_DATASET_HEADER
#define DATAVISUALIZER_DATASET_HEADER
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <iostream>
namespace DataVisualizer {
template<typename T>
class DataSet {
public:
	DataSet() :
			_size(128), _data((T*)malloc(128*sizeof(T))) {
	}
	;
	DataSet(const std::vector<T>& data) :
			_size(data.size()), _data((T*)malloc(data.size()*sizeof(T))) {
		std::copy(data.begin(), data.end(), _data);
	}
	DataSet(T* data,std::size_t size):_size(size), _data((T*)malloc(size*sizeof(T))){
		memcpy(_data,data,size*sizeof(T));
	}
	T& operator[] (const int index){
		return _data[index];
	}

protected:
private:
	std::size_t _size;
	T* _data;
};

}

#endif
