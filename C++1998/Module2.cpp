
#include "Module2.h"

extern "C" 
Module * create() {
    return new Module2;
}

extern "C" 
void destroy(Module* p) {
    delete p;
}


#include <iostream>
using namespace std;

Module2::Module2(){
}

void Module2::registerModule(){
	cout<<"Hi this is Module2. Today is a nice day."<<endl;
}
