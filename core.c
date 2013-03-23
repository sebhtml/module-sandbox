#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void load_module(const char*module_file){

	void * module_handle = NULL;

	void (*register_module)() = NULL;

	module_handle = open_library(module_file);

	register_module = read_symbol(module_handle, "register_module");

	register_module();

	close_library(module_handle);
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
			fscanf(fp, "%s", buffer);

			printf("[core.c] loading module %s\n", buffer);
			load_module(buffer);
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
