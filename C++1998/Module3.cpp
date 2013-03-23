
#include "Module3.h"

extern "C" 
Module * create() {
    return new Module3;
}

extern "C" 
void destroy(Module* p) {
    delete p;
}


#include <iostream>
using namespace std;

Module3::Module3(){
}

void Module3::registerModule(){
	cout<<"Hi this is Module3 -- how are you ?"<<endl;
}
