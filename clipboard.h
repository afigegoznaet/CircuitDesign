#ifndef CLIPBOARD_H
#define CLIPBOARD_H
#include "Elements/circuitelement.h"

class ClipBoard
{
private:
	ClipBoard();
	CircuitElement* circPtr = nullptr;
	static ClipBoard* singleton;
public:
	static ClipBoard* getInstance();
	static void getRidOfInstance();
	bool isEmpty(){return circPtr == nullptr;}
	void cut(CircuitElement* circPtr);
	void copy(CircuitElement* circPtr);
	CircuitElement* paste();
};

#endif // CLIPBOARD_H
