// loader.cpp
#include "spdlog/spdlog.h"
#include <EX.h>
#include <cstdio>

// FIXME : ADD MICRO TO MAKE THE PROGRAM CROSS PLATFORM
#include <cstdlib>
#include <dlfcn.h> // For Linux; use windows.h for Windows





void get_function(const char *path , const char * function_name, void **Func) {
  spdlog::info("try to load {}", path);
  void *handle = dlopen(path, RTLD_LAZY);// FIXME : in windows we need to use dll
  if (!handle) {
    fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(1); 
  }

  spdlog::info("get the function {}", function_name);
  *Func = dlsym(handle, function_name);
  if (!*Func) {
    fprintf(stderr, "Error locating sort function: %s\n", dlerror());
    exit(1);
  }else {
  spdlog::info("{} loaded", function_name);
  }
}



void load_exercice(const char *path_libEX , void**ex, void**test , void ** parse_init) {
  get_function(path_libEX, "ex", ex);
  get_function(path_libEX, "test", test);
  get_function(path_libEX, "parse_init", parse_init);
}
