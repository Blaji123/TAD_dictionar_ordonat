#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

// complexitate : Theta(1)
Iterator::Iterator(const DO& d) : dict(d){
	currentNode = dict.head;
}

// complexitate : Theta(1)
void Iterator::prim(){
	currentNode = dict.head;
}

// complexitate : Theta(1)
void Iterator::urmator(){
    if(valid())
	    currentNode = currentNode->next_element();
    else{
        throw std::exception();
    }
}

// complexitate : Theta(1)
bool Iterator::valid() const{
	return currentNode!= nullptr;
}

// complexitate : Theta(1)
TElem Iterator::element() const{
	if(valid()) {
        return currentNode->element();
    }else
        throw std::exception();
}


