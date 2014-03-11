#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "List.h"
#include "../io/OutputStream.h"
#include <cassert>
#include <cstdio>

namespace ycg {

template <class T>
class ArrayList : public List<T> {
public:
	ArrayList();
	explicit ArrayList(int size);
	ArrayList(int size, int capacity);
	ArrayList(const ArrayList<T>& orig);
	ArrayList(ArrayList<T>&& orig);
	~ArrayList();
	ArrayList<T>& operator = (const ArrayList<T>& rhs);
	ArrayList<T>& operator = (ArrayList<T>&& rhs);
	int size() const { return _size; }
	ArrayList<T>& add(const T& elem);
	const T& get(int index) const;
	ArrayList<T>& set(int index, const T& elem);
	const T& operator [] (int index) const;
	T& operator [] (int index);
	bool isEmpty() const;
	void clear();
	void reserve(int capacity);
	int indexOf(const T& elem) const;

//	operator ==
//	operator !=
//	operator <
	class Iterator;
	friend class Iterator;
	class Iterator {
	private:
		Iterator(ArrayList<T>&, int index);
	private:
		ArrayList<T>& list;
		int currentIndex;
	};
	const T* begin() const { return _data; }
	T* begin() { return _data; }
	const T* end() const { return _data + _size;}
	T* end() { return _data + _size;}
	template <class T> friend OutputStream& operator << (OutputStream& os, const ArrayList<T>& list);
private:
	void expandCapacity();
private:
	static const int MIN_CAPACITY;
	int _size;
	int _capacity;
	T* _data;
};

template <class T>
const int ArrayList<T>::MIN_CAPACITY = 1 + 32 / sizeof(T);

template <class T>
ArrayList<T>::ArrayList() :
	_size(0),
	_capacity(MIN_CAPACITY) {
	_data = new T[MIN_CAPACITY];
}

template <class T>
ArrayList<T>::ArrayList(int size) :
	_size(size),
	_capacity(size),
	_data(new T[size]){
	for (int i = 0; i < size; ++i) {
		_data[i] = T();
	}
}

template <class T>
ArrayList<T>::ArrayList(int size, int capacity) :
	_size(size),
	_capacity(capacity),
	_data(new T[capacity]) {
	for (int i = 0; i < size; ++i) {
		_data[i] = T();
	}
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& orig) :
	_size(orig._size),
	_capacity(orig._capacity),
	_data(new T[orig._capacity]) {
	for (int i = 0; i < _size; ++i) {
		_data[i] = orig._data[i];
	}
}

template <class T>
ArrayList<T>::ArrayList(ArrayList<T>&& orig) :
	_size(orig._size),
	_capacity(orig._capacity),
	_data(orig._data){
	orig._data = nullptr;
}

template <class T>
ArrayList<T>::~ArrayList() {
	delete []_data;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator = (const ArrayList<T>& rhs) {
	if (this == &rhs) return *this;
	delete []_data;
	_size = rhs._size;
	_capacity = rhs._capacity;
	_data = new T[_capacity];
	for (int i = 0; i < _size; ++i) {
		_data[i] = rhs._data[i];
	}
}

template <class T>
ArrayList<T>& ArrayList<T>::operator =(ArrayList<T>&& rhs) {
	if (this == &rhs) return *this;
	delete []_data;
	_size = rhs._size;
	_capacity = rhs._capacity;
	_data = rhs._data;
	rhs._data = nullptr;
}

template <class T>
ArrayList<T>& ArrayList<T>::add(const T& elem) {
	if (_size == _capacity-1) {
		expandCapacity();
	}
	_data[_size++] = elem;
	return *this;
}

template <class T>
const T& ArrayList<T>::get(int index) const {
	assert(index >= 0 && index < _size);
	return _data[index];
}

template <class T>
ArrayList<T>& ArrayList<T>::set(int index, const T& elem) {
	assert(index >= 0 && index < _size);
	_data[index] = elem;
	return *this;
}

template <class T>
inline const T& ArrayList<T>::operator [] (int index) const {
	return _data[index];
}

template <class T>
inline T& ArrayList<T>::operator [] (int index) {
	return _data[index];
}

template <class T>
void ArrayList<T>::clear() {
	_size = 0;
}

template <class T>
void ArrayList<T>::reserve(int capacity) {
	int capacityNew = capacity;
	T *dataNew = new T[capacityNew];
	for (int i = 0; i < _size; ++i) {
		dataNew[i] = _data[i];
	}
	delete []_data;
	_capacity = capacityNew;
	_data = dataNew;
}

template <class T>
int ArrayList<T>::indexOf(const T& elem) const {
	for(int i = 0; i < _size; ++i) {
		if (_data[i] == elem) {
			return i;
		}
	}
	return -1;
}


template <class T>
void ArrayList<T>::expandCapacity() {
	int capacityNew = _capacity * 2;
	T *dataNew = new T[capacityNew];
	for (int i = 0; i < _capacity; ++i) {
		dataNew[i] = _data[i];
	}
	delete []_data;
	_capacity = capacityNew;
	_data = dataNew;
}

template <class T>
OutputStream& operator << (OutputStream& os, const ArrayList<T>& list) {
	os << "[";
	for (int i = 0; i < list._size-1; ++i) {
		os << list._data[i] << ", ";
	}
	os << list._data[list._size-1] << "]";
	return os;
}

} //~ namespace ycg

#endif // ARRAYLIST_H
