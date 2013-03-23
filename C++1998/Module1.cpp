
#include "Module1.h"

extern "C" 
Module * create() {
    return new Module1;
}

extern "C" 
void destroy(Module* p) {
    delete p;
}


#include <iostream>
using namespace std;

Module1::Module1(){
}

void Module1::registerModule(){
	cout<<"Hi this is Module1"<<endl;
}
