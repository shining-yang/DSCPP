//
// File: NewHandler.cpp
//
// Customized exception handler for memory allocation
//
// Shining Yang <y.s.n@live.com>, 2014/09/02
//
#include <new.h>
#include "NewHandler.h"

class OutOfMemory
{
public:
    OutOfMemory() {}
    ~OutOfMemory() {}
};

int MyNewHandler(size_t)
{
    throw new OutOfMemory();
}

// Global variable to hold the previous new handler
int (*g_PreviousNewHandler)(size_t) = 0;

void ApplyCustomNewHandler()
{
    g_PreviousNewHandler = _set_new_handler(MyNewHandler);
}

void RestoreOriginalNewHandler()
{
    _set_new_handler(g_PreviousNewHandler);
}
