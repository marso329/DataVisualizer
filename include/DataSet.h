#ifndef DATAVISUALIZER_DATASET_HEADER
#define DATAVISUALIZER_DATASET_HEADER

//standard includes
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdexcept>
#include <atomic>


//own includes
#include "Vertex.h"

inline std::size_t pow2roundup(std::size_t x) {
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

//own includes
#include "Constants.h"

namespace DataVisualizer {
template<typename T>
class DataSet {
public:
	//Normal constructor, allocates a predefined amount of memory
	DataSet() :
			_size(0), _real_size(INITIAL_SIZE_DATASET), _data(
					(T*) malloc(INITIAL_SIZE_DATASET * sizeof(T))), _shared_data(
					_data,::free), _dirty(false),update(false) {
	}
	;
	//Copies the data in the vector into memory
	DataSet(const std::vector<T>& data) :
			_size(data.size()), _real_size(data.size()), _data(
					(T*) aligned_alloc(MEMORY_ALIGNMENT,
							data.size() * sizeof(T))), _shared_data(_data,::free), _dirty(
					false),update(true) {
		std::copy(data.begin(), data.end(),_data);
	}

	//Copies the data from the pointer into memory
	DataSet(T* data, std::size_t size) :
			_size(size), _real_size(size), _data(
					(T*) aligned_alloc(MEMORY_ALIGNMENT, size * sizeof(T))), _shared_data(
					_data,::free), _dirty(false),update(false) {
		memcpy(_data, data, size * sizeof(T));
	}

	~DataSet(){
	//	delete _shared_data;
	}

	//Subscript operator, extends memory if out of bound
	T& operator[](const int pos) {
		if (static_cast<std::size_t>(pos) > _real_size) {
			extend_memory(static_cast<std::size_t>(pos));
		}
		if (static_cast<std::size_t>(pos) > _size) {
			_size = pos;
		}
		return _data[pos];
	}

	//access to shared_ptr
	std::shared_ptr<T> get_pointer() {
		return _shared_data;
	}

	//Set the data dirty so it will be updated
	void set_dirty() {
		_dirty = true;
	}

	//Function for setting specific element
	void set_data(const T& data, std::size_t pos) {
		if (pos > _real_size) {
			extend_memory(static_cast<std::size_t>(pos));
		}
		if (pos > _size) {
			_size = pos;
		}
		*(_data + pos) = data;
		_dirty = true;
	}
	void copy_data(T* data, std::size_t size) {
		if (size > _real_size) {
			extend_memory(static_cast<std::size_t>(size));
		}
		memcpy(_data,data,size*sizeof(T));
		_dirty=true;

	}

	void copy_data(T* data, std::size_t size,std::size_t offset) {
		if (size+offset > _real_size) {
			extend_memory(static_cast<std::size_t>(size+offset));
		}
		memcpy(_data+offset,data,size*sizeof(T));
		_dirty=true;
	}
	void enable_update(){
		update=true;
	}
	void disable_update(){
		update=false;
	}


protected:
private:
	void extend_memory(std::size_t size) {
		std::size_t new_size = pow2roundup(static_cast<std::size_t>(size));
		T* new_ptr = (T*) aligned_alloc(MEMORY_ALIGNMENT, new_size * sizeof(T));
		memcpy(new_ptr, _data, _size * sizeof(T));
		_shared_data.reset(new_ptr,::free);
		_real_size = new_size;
		_data = new_ptr;
	}
	void update_center_points(){
		_center.resize(_size);
	}

	//numbers of element in series
	std::size_t _size;
	//numbers of allocated series
	std::size_t _real_size;
	//pointer to data
	T* _data;
	std::shared_ptr<T> _shared_data;
	bool _dirty;
	std::atomic<bool> update;
	std::vector<Vertex> _center;
};

}

#endif
