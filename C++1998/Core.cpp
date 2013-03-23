#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Module.h"

#include <iostream>
using namespace std;

#define false 0
#define true 1

/**
 * \see http://en.wikipedia.org/wiki/Dynamic_loading
 * \see http://stackoverflow.com/questions/6649936/c-compiling-on-windows-and-linux-ifdef-switch
 */

#ifdef __unix__
#include <dlfcn.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

void*open_library(const char*file){

	void*module_handle = NULL;

#ifdef __unix__
	char * error = NULL;

	module_handle = dlopen(file, RTLD_LAZY);
	error = dlerror();
	if (!module_handle) {
    		fprintf (stderr, "%s\n", error);
    		exit(EXIT_FAILURE);
	}

#elif defined(_WIN32)
	HMODULE library = LoadLibrary(file);

	module_handle = (void*)library;
#endif

	return module_handle;
}

void*read_symbol(void*module_handle,const char*symbol){

	void * symbol_handle = NULL;

#ifdef __unix__
	symbol_handle = dlsym(module_handle, symbol);

	char*error = dlerror();

	if (error != NULL)  {
    		fprintf (stderr, "%s\n", error);
    		exit(EXIT_FAILURE);
	}

#elif defined(_WIN32)
	FARPROC initializer = GetProcAddress(module_handle, symbol);

	if(initializer == NULL){
		exit(EXIT_FAILURE);
	}

	symbol_handle = (void*)initializer;
#endif

	return symbol_handle;
}

void close_library(void*module_handle){

#ifdef __unix__

	dlclose(module_handle);
#elif defined(_WIN32)
	FreeLibrary(module_handle);
#endif
}

/**
 * \see http://www.isotton.com/devel/docs/C++-dlopen-mini-HOWTO/C++-dlopen-mini-HOWTO.html
 */
Module*load_module(const char*module_file){

	void * module_handle = NULL;
	module_handle = open_library(module_file);

	create_t*create= (create_t*)read_symbol(module_handle, "create");

	Module*instance = create();

	// TODO: destroy the module too !
	//destroy_t*destroy=(destroy_t*)read_symbol(module_handle, "destroy");
	// destroy(instance);
	//close_library(module_handle);

	return instance;
}

int main(int argc, char **argv) {

	if(argc==1){
		printf("You must provide a configuration!\n");
		exit(EXIT_FAILURE);
	}

	const char*configuration=argv[1];

	FILE*fp=fopen(configuration,"r");

	char buffer[256];

	const char load_module_operation_code[] = "LoadModule";
	int match=0;

	while(!feof(fp)){
		fscanf(fp, "%s", buffer);

		if(strcmp(buffer, load_module_operation_code) == match){

			char moduleFile[128];

			fscanf(fp, "%s", moduleFile);

			printf("[core.c] loading module %s\n", moduleFile);
			Module*module = load_module(moduleFile);

			module->registerModule();
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
