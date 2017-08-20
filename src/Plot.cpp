#include "Plot.h"

namespace DataVisualizer {

template<>
void Plot<bool>::set_type() {
	_type = BOOL;
}

template<>
void Plot<char>::set_type() {
	_type = CHAR;
}
template<>
void Plot<unsigned char>::set_type() {
	_type = UNSIGNED_CHAR;
}

template<>
void Plot<short>::set_type() {
	_type = SHORT;
}

template<>
void Plot<unsigned short>::set_type() {
	_type = UNSIGNED_SHORT;
}

template<>
void Plot<int>::set_type() {
	_type = INT;
}

template<>
void Plot<unsigned>::set_type() {
	_type = UNSIGNED;
}

template<>
void Plot<long>::set_type() {
	_type = LONG;
}

template<>
void Plot<unsigned long>::set_type() {
	_type = UNSIGNED_LONG;
}

template<>
void Plot<long long>::set_type() {
	_type = LONG_LONG;
}

template<>
void Plot<unsigned long long>::set_type() {
	_type = UNSIGNED_LONG_LONG;
}

template<>
void Plot<float>::set_type() {
	_type = FLOAT;
}

template<>
void Plot<double>::set_type() {
	_type = DOUBLE;
}


template<>
void Plot<long double>::set_type() {
	_type = LONG_DOUBLE;
}
}
