#include <optional>

#include "deps/json.hpp"

using json = nlohmann::json;

class LibreTranslateAPI {
  private:
    std::string base_url;
    std::optional<std::string> api_key;

  public:
    LibreTranslateAPI(std::string base_url="https://translate.argosopentech.com/",
		      std::optional<std::string> api_key = std::nullopt);
    json translate(std::string q, std::string source, std::string target);
    json languages();
    json detect(std::string q);
};

