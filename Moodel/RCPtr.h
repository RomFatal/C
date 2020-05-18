#pragma once


#ifndef _RCRTPTR_HPP
#define _RCRTPTR_HPP 1

template<class  T>
class RCPtr
{
public:
	RCPtr(T* realPtr  );
	RCPtr(const RCPtr& rhs);
	~RCPtr();
	RCPtr& operator=(const RCPtr& rhs);
	T* operator->() const;
	T& operator*() const;
	T *pointee;
private:

	void init();
};


template<class T>
RCPtr<T>::RCPtr(T* realPtr) : pointee(realPtr)
{
	init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr<T>& rhs) : pointee(rhs.pointee)
{
	init();
}

template<class T>
void RCPtr<T>::init()
{
	if (pointee == 0)
		return;
	if (pointee->isShareable() == false)
		pointee = new T(*pointee); // shareable, copy it
	pointee->addReference();
}

template<class T>
T* RCPtr<T>::operator->() const
{
	return pointee;
}
template<class T>
T& RCPtr<T>::operator*() const
{
	return *pointee;
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs)
{
	if (pointee != rhs.pointee) 
	{ // where the value
	// doesn't change
		if (pointee)
		{
			pointee->removeReference(); // remove reference to
		} // current value
		pointee = rhs.pointee; // point to new value
		init(); // if possible, share it
	} // else make own copy
	return *this;
}


template<class T>
RCPtr<T>::~RCPtr()
{
	if (pointee)pointee->removeReference();
}

template <class V>
class nodeType {
public:
	RCPtr<V> Val;//smart Shared pointer to 
	nodeType<V>* next;
	nodeType<V>(RCPtr<V>& nSmartPointer, nodeType<V>* nextNode)
		: Val(nSmartPointer), next(nextNode) {

	}
	nodeType<V>(V* realPtr, nodeType<V>* nextNode)
		: Val(realPtr), next(nextNode) {

	}
};
#endif
