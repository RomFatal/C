#pragma once
#ifndef _RCIPtr_HPP
#define _RCIPtr_HPP 1
#include "RCObject.h"
template<class T>
class RCIPtr
{
public:
	RCIPtr(T* realPtr = 0);
	RCIPtr(const RCIPtr& rhs);
	~RCIPtr();
	RCIPtr& operator=(const RCIPtr& rhs);
	const T* operator->() const;
	T* operator->();
	const T& operator*() const;
	T& operator*();
private:
	struct CountHolder : public RCObject // the nested
	{ // CountHolder
		~CountHolder() { delete pointee; }
		T *pointee;
	};
	CountHolder *counter;
	void init();
	void makeCopy(); // see below
};

#endif
