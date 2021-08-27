# LibreTranslate-cpp
[LibreTranslate](https://libretranslate.com) C++17 bindings.

## [Example usage](main.cpp)
```
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

```

```
translate:
{"translatedText":"Hola Mundo"}

languages:
[{"code":"en","name":"English"},{"code":"ar","name":"Arabic"},{"code":"zh","name":"Chinese"},{"code":"fr","name":"French"},{"code":"de","name":"German"},{"code":"hi","name":"Hindi"},{"code":"id","name":"Indonesian"},{"code":"ga","name":"Irish"},{"code":"it","name":"Italian"},{"code":"ja","name":"Japanese"},{"code":"ko","name":"Korean"},{"code":"pl","name":"Polish"},{"code":"pt","name":"Portuguese"},{"code":"ru","name":"Russian"},{"code":"es","name":"Spanish"},{"code":"tr","name":"Turkish"},{"code":"vi","name":"Vietnamese"}]

detect:
[{"confidence":92.0,"language":"en"}]
```


## Dependencies
[libcurl](https://curl.se/libcurl/c/http-post.html):
```
sudo apt-get install -y libcurl4-openssl-dev
curl-config --libs
```

[nlohmann/json](https://github.com/nlohmann/json):

Single file included in source

## Building
```
make
```

## Running
```
./libretranslate
```

## Clean
```
make clean
```
