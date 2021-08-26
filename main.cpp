#include <iostream>
#include <curl/curl.h>

class LibreTranslateAPI {
  std::string DEFAULT_URL = "https://translate.argosopentech.com/";

  public:
    std::string translate(std::string q, std::string source, std::string target){
	return "Hello Mars";
    }
};

size_t curl_writeback_fun(void* contents, size_t size, size_t nmemb, std::string *s) {
  size_t len = size * nmemb;
  s->append((char*)contents, len);
  return len;
}

int main(){
  std::string s;

  // Based on https://curl.se/libcurl/c/http-post.html
  // Daniel Stenberg, <daniel@haxx.se>, et al.
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://translate.argosopentech.com/translate");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"q\":\"hello\",\"source\":\"en\",\"target\":\"es\"}");

    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writeback_fun);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    curl_slist_free_all(headers);
 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  std::cout << s << std::endl;
  return 0;
}
