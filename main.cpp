#include "LibreTranslate.h"

int main(){
  LibreTranslateAPI libreTranslateAPI;
  std::cout << libreTranslateAPI.translate("Hello World", "en", "es") << std::endl;
  return 0;
}
