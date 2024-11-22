#include "loader.h"
#include <EX.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <spdlog/spdlog.h>
#include <string>

enum ARGINDEX {
  EXERCICE = 1,
  SOLUTION = 2,
  JSON = 3,
};

int main(int argc, char const *argv[]) {
  spdlog::set_pattern("[%H:%M:%S] %^[%l] [%v]%$");
  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  nlohmann::json __json;
  try {
    spdlog::info("Raw JSON input: |{}|", argv[JSON]);
    __json = nlohmann::json::parse(argv[JSON]);
    spdlog::info("Parsed JSON: {}", __json.dump(4)); // Pretty-print JSON for debugging
  } catch (const nlohmann::json::exception &e) {
    spdlog::error("JSON Parsing Error: {}", e.what());
    return -1; // Exit early with error
  }

  ex_t(___ex);
  test_t(___test);
  parse_init_t(___parse_init);

  load_exercice(argv[EXERCICE], (void **)&___ex,(void **)& ___test,(void **)& ___parse_init);


  EX::__input_t *__input = nullptr;
  EX::__output_t *__output = nullptr;
  EX::__result_t *__result = nullptr;
  EX::__return_t *__return = nullptr;
  spdlog::info("BRUH");

  ___parse_init(&__json, &__result, &__return, &__input, &__output);
  ___ex(__result, __return, __input, __output, argv[SOLUTION]);
  ___test(__result, __return, __input, __output);
  spdlog::info("The result is {}", *((bool *)__result) ? "true" : "false");

  return 0;
}
