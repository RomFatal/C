#include "RCIPtr.h"


template<class T>
void RCIPtr<T>::init()
{
	if (counter->isShareable() == false)
	{
		T *oldValue = counter->pointee;
		counter = new CountHolder;
		counter->pointee = new T(*oldValue);
	}
	counter->addReference();
}
template<class T>
RCIPtr<T>::RCIPtr(T* realPtr)
	: counter(new CountHolder)
{
	counter->pointee = realPtr;
	init();
}
template<class T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs)
	: counter(rhs.counter)
{
	init();
}

template<class T>
RCIPtr<T>::~RCIPtr()
{
	counter->removeReference();
}
template<class T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
{
	if (counter != rhs.counter)
	{
		counter->removeReference();
		counter = rhs.counter;
		init();
	}
	return *this;
}

template<class T> // implement the copy
void RCIPtr<T>::makeCopy() // part of copy-on-
{ // write (COW)
	if (counter->isShared())
	{
		T *oldValue = counter->pointee;
		counter->removeReference();
		counter = new CountHolder;
		counter->pointee = new T(*oldValue);
		counter->addReference();
	}
}
template<class T> // const access;
const T* RCIPtr<T>::operator->() const // no COW needed
{
	return counter->pointee;
}
template<class T> // non-const
T* RCIPtr<T>::operator->() // access; COW
{ // needed
	makeCopy(); return counter->pointee;
}

template<class T> // const access;
const T& RCIPtr<T>::operator*() const // no COW needed
{
	return *(counter->pointee);
}
template<class T> // non-const
T& RCIPtr<T>::operator*() // access; COW
{ // needed
	makeCopy(); return *(counter->pointee);
}