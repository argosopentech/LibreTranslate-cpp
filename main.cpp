#include <iostream>

#include "LibreTranslate.h"

int main(){
  LibreTranslateAPI libreTranslateAPI;
  std::cout << "translate:" << std::endl;
  std::cout << libreTranslateAPI.translate("Hello World", "en", "es") << std::endl;
  std::cout << std::endl << "languages:" << std::endl;
  std::cout << libreTranslateAPI.languages() << std::endl;
  std::cout << std::endl << "detect:" << std::endl;
  std::cout << libreTranslateAPI.detect("Hello World") << std::endl;
  return 0;
}
