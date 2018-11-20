//
// File: NewHandler.cpp
//
// Customized exception handler for memory allocation
//
// Shining Yang <y.s.n@live.com>, 2014/09/02
//
#include <new>
#include "NewHandler.h"

class OutOfMemory {
 public:
  OutOfMemory() {}
  ~OutOfMemory() {}
};

void MyNewHandler() {
  throw new OutOfMemory();
}

// Global variable to hold the previous new handler
void (*g_PreviousNewHandler)() = 0;

void ApplyCustomNewHandler() {
  g_PreviousNewHandler = std::set_new_handler(MyNewHandler);
}

void RestoreOriginalNewHandler() {
  std::set_new_handler(g_PreviousNewHandler);
}
