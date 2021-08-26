#include <iostream>
#include <vector>

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

std::string curl_post(std::string url, std::vector<std::string> headers, std::string post_fields){
  // Based on https://curl.se/libcurl/c/http-post.html
  // Daniel Stenberg, <daniel@haxx.se>, et al.

  std::string to_return;
  CURL *curl;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);

    struct curl_slist *headers_slist = NULL;
    if(headers.size() > 0){
	for(std::string header : headers){
	  headers_slist = curl_slist_append(headers_slist, header.c_str());
	}
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers_slist);
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writeback_fun);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &to_return);

    CURLcode res;
    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
      throw curl_easy_strerror(res);
    }

    if(headers_slist){
      curl_slist_free_all(headers_slist);
    }
 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return to_return;
}

int main(){
  std::string url = "https://translate.argosopentech.com/translate";
  std::string post_fields = "{\"q\":\"hello\",\"source\":\"en\",\"target\":\"es\"}";
  std::vector<std::string> headers;
  headers.push_back("Content-Type: application/json");
  std::string s = curl_post(url, headers, post_fields);

  std::cout << s << std::endl;
  return 0;
}
