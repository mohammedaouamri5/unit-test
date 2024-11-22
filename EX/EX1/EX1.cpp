#define JSON_NO_EXTERNAL_LIBRARY
#include "EX.h"
#include "loader.h"
#include <dlfcn.h>

namespace EX {
struct __input_t {
  int *arr;
  int len;
};

struct __output_t {
  int *arr;
  int len;
};

struct __return_t {};

struct __result_t {
  bool status;
};

void ex(__result_t *result, __return_t *__return, __input_t *in,
        __output_t *out, const char __solution_path[]) {
  void (*sort_function)(int *, int);
  get_function(__solution_path, "sort", (void **)&sort_function);
  sort_function(in->arr, in->len);
}

void parse_init(nlohmann::json *__json, __result_t **result, __return_t **__return,
           __input_t **in, __output_t **out) {

  *in = (__input_t *)malloc(sizeof(__input_t));
  *out = (__output_t *)malloc(sizeof(__output_t));
  *result = (__result_t *)malloc(sizeof(__result_t));
  *__return = (__return_t *)malloc(sizeof(__return_t));

  try {

    /* parse input */ {
      (*in)->len = (*__json)["casse"]["size"].get<int>();
      (*in)->arr = (int *)malloc((*in)->len * sizeof(int));
      memcpy((*in)->arr,
             (*__json)["casse"]["tab"].get<std::vector<int>>().data(),
             (*in)->len * sizeof(int));
    }

    /* parse output */ {
      (*out)->len = (*__json)["corect"]["size"].get<int>();
      (*out)->arr = (int *)malloc((*out)->len * sizeof(int));
      memcpy((*out)->arr,
             (*__json)["corect"]["tab"].get<std::vector<int>>().data(),
             (*out)->len * sizeof(int));
    }

  } catch (const nlohmann::json::exception &e) {
    exit(1);
  }
}

void test(__result_t *result, __return_t *__return, __input_t *in,
          __output_t *out) {
  if (in->len != out->len) {
    result->status = false;
    return;
  }

  for (int i = 0; i < in->len; i++) {
    if (in->arr[i] != out->arr[i]) {
      result->status = false;
      return;
    }
  }
  result->status = true;
}

nlohmann::json parse_result(__result_t *result, __return_t *__return, __input_t *in,
                     __output_t *out) {return  nlohmann::json{{"status", result->status}};}
} // namespace EX
