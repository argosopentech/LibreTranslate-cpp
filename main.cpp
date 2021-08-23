#include <iostream>

class LibreTranslateAPI {
  std::string DEFAULT_URL = "https://translate.argosopentech.com/";

  public:
  std::string translate(std::string q, std::string source, std::string target){
    return "Hello Mars";
  }

};

int main(){
  LibreTranslateAPI libreTranslateAPI;
  std::cout << libreTranslateAPI.translate("Hello World", "en", "es") << std::endl;
  return 0;
}
