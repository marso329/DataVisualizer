#ifndef DATAVISUALIZER_PLOT_HEADER
#define DATAVISUALIZER_PLOT_HEADER
#include "DataSets.h"
#include <type_traits>

namespace DataVisualizer {



enum TYPE {BOOL,CHAR,UNSIGNED_CHAR, SHORT, UNSIGNED_SHORT,INT,UNSIGNED,LONG,UNSIGNED_LONG,LONG_LONG,UNSIGNED_LONG_LONG,FLOAT,DOUBLE,LONG_DOUBLE,UNDEFINED };

class PlotBase{
public:
	PlotBase(){

	}
	virtual ~PlotBase(){};
protected:
TYPE _type=UNDEFINED;
private:

};

template<typename T>
class Plot:public PlotBase {
	static_assert((std::is_integral<T>::value||std::is_floating_point<T>::value), "T must inherit from list");
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
	void set_type(){
		_type=UNDEFINED;
	}
	float front_vertical_left_space=FVLSPACE;
	float front_vertical_right_space=FVRSPACE;
	float right_vertical_left_space=RVLSPACE;
	float right_vertical_right_space=RVRSPACE;
	float upper_space=USPACE;
	float lower_space=LSPACE;
	DataSets<T>* _datasets;
};

}

#endif
