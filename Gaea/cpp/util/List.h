#ifndef LIST_H
#define LIST_H

namespace ycg {

template <class T>
class List {
public:
	List();
	virtual ~List() = 0;
	virtual int size() const = 0;
	virtual List<T>& add(const T& elem) = 0;
	virtual const T& get(int index) const = 0;
	virtual void clear() = 0;
//	virtual void add(int index, T element);

//	virtual void remove(T element);
};

template <class T>
List<T>::List() { }

template <class T>
List<T>::~List() { }

} //~ namespace ycg

#endif /* LIST_H */
