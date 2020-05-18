#pragma once

#ifndef _RCOBJECT_HPP
#define _RCOBJECT_HPP 1

class RCObject // base class for reference-
{ // counted objects
public:
	void addReference();
	void removeReference();
	void markUnshareable();
	bool isShareable() const;
	bool isShared() const;
protected:
	RCObject();
	RCObject(const RCObject& rhs);
	RCObject& operator=(const RCObject& rhs);
	virtual ~RCObject() = 0;
private:
	int refCount;
	bool shareable;

};

#endif