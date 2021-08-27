#include <iostream>
#include <vector>

#include <curl/curl.h>
#include "deps/json.hpp"

using json = nlohmann::json;


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

json json_post(std::string url, json data){
  std::vector<std::string> headers;
  headers.push_back("Content-Type: application/json");

  std::string serialized_json = data.dump();
  
  std::string res = curl_post(url, headers, serialized_json);

  return json::parse(res);
}

class LibreTranslateAPI {
  private:
    std::string base_url;

  public:
    LibreTranslateAPI(std::string base_url="https://translate.argosopentech.com/translate");
  
    json translate(std::string q, std::string source, std::string target);
};

LibreTranslateAPI::LibreTranslateAPI(std::string base_url)
  : base_url(base_url){}

json LibreTranslateAPI::translate(std::string q, std::string source, std::string target){
  json req;
  req["q"] = q;
  req["source"] = source;
  req["target"] = target;

  json res = json_post("https://translate.argosopentech.com/translate", req);

  return res;
}


