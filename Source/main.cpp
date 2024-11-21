#include "EX.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <spdlog/spdlog.h>
#include <string>




int main(int argc, char const *argv[]) {
  spdlog::set_pattern("[%H:%M:%S] %^[%l] [%v]%$");
  spdlog::set_level(spdlog::level::debug); // Set global log level to debug

  nlohmann::json __json;
  try {
    spdlog::info("Raw JSON input: |{}|", argv[2]);
    __json = nlohmann::json::parse(argv[2]);
    spdlog::info("Parsed JSON: {}",
                 __json.dump(4)); // Pretty-print JSON for debugging
  } catch (const nlohmann::json::exception &e) {
    spdlog::error("JSON Parsing Error: {}", e.what());
    return -1; // Exit early with error
  }
  EX::__input_t *__input = nullptr;
  EX::__output_t *__output = nullptr;
  EX::__result_t *__result = nullptr;
  EX::__return_t *__return = nullptr;

  EX::parse_init(&__json, &__result, &__return, &__input, &__output) ;
  EX::ex(__result, __return, __input, __output, argv[1]);
  EX::test(__result, __return, __input, __output); 
  spdlog::info("The result is {}", *((bool*)__result) ? "true" : "false");

  return 0;
}
