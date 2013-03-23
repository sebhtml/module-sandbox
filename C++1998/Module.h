
#ifndef _Module_h
#define _Module_h

class Module{

public:
	virtual void registerModule() = 0;
	virtual ~Module() = 0;
};

typedef Module * create_t();
typedef void destroy_t(Module*);

#endif
