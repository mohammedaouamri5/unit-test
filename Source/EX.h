#ifndef __EX_H__
#define __EX_H__
#include <nlohmann/json.hpp>

extern "C" {
namespace EX {

struct __input_t;
struct __output_t;
struct __result_t;
struct __return_t;
void ex(__result_t *result, __return_t *__return, __input_t *in,
        __output_t *out, const char __solution_path[]);

void parse_init(nlohmann::json *__json, __result_t **result,
                __return_t **__return, __input_t **in, __output_t **out);

void test(__result_t *result, __return_t *__return, __input_t *in,
          __output_t *out);

} // namespace EX
} // namespace EX
#endif // __EX_H__
