
#include "EX.h"
#include "loader.h"
#include "spdlog/fmt/bundled/core.h"
#include "spdlog/spdlog.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <semaphore.h>
#include <sys/types.h>

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
  spdlog::info("run");
  sort_function(in->arr, in->len);
  spdlog::info("run done");
}

void parse_init(nlohmann::json *__json, __result_t **result,
                __return_t **__return, __input_t **in, __output_t **out) {

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
    spdlog::warn("JSON Parsing Error: {}", e.what());
    exit(1);
  }
}

void test(__result_t *result, __return_t *__return, __input_t *in,
          __output_t *out) {
  if (in->len != out->len) {
    result->status = false;
    return;
  }

  for (int i = 0; i < out->len; i++) {
    spdlog::info("out[{}]: {}  in[{}]: {}", i, out->arr[i], i, in->arr[i]); 
    if (in->arr[i] != out->arr[i]) {
      result->status = false;
      // return;
    }
  }
  result->status = true;
}

} // namespace EX
