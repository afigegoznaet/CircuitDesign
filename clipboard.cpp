#include "clipboard.h"

ClipBoard* ClipBoard::singleton = nullptr;

ClipBoard::ClipBoard(){

}

ClipBoard *ClipBoard::getInstance(){
	if(nullptr == singleton){
		singleton = new ClipBoard;
	}
	return singleton;
}
void ClipBoard::getRidOfInstance(){
	delete singleton;
	singleton = nullptr;
}

void ClipBoard::cut(CircuitElement* circPtr){
	copy(circPtr);
}

void ClipBoard::copy(CircuitElement* circPtr){
	delete this->circPtr;
	this->circPtr = circPtr->clone();

}
CircuitElement* ClipBoard::paste(){
	if(circPtr == nullptr)
		return circPtr;
	return circPtr->clone();
}
