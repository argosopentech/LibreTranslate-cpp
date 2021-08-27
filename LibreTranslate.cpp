#include "LibreTranslate.h"

#include <vector>

#include <curl/curl.h>

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

LibreTranslateAPI::LibreTranslateAPI(std::string base_url, std::optional<std::string> api_key)
  : base_url(base_url), api_key(api_key){}

json LibreTranslateAPI::translate(std::string q, std::string source, std::string target){
  std::string url = base_url + "translate";
  
  json req;
  req["q"] = q;
  req["source"] = source;
  req["target"] = target;

  if(api_key){
    req["api_key"] = api_key.value();
  }

  json res = json_post(url, req);

  return res;
}

json LibreTranslateAPI::languages(){
  std::string url = base_url + "languages";
  
  json req;

  json res = json_post(url, req);

  return res;
}

json LibreTranslateAPI::detect(std::string q){
  std::string url = base_url + "detect";
  
  json req;
  req["q"] = q;

  if(api_key){
    req["api_key"] = api_key.value();
  }

  json res = json_post(url, req);

  return res;
}
