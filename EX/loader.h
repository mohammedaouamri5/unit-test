#ifndef __LOADER_H__
#define __LOADER_H__
void get_function(const char *path, const char *function_name,
                  void **sort_function);
void load_exercice(const char *path_libEX, void **ex, void **test,
                   void **parse_init);

#endif // __LOADER_H__
