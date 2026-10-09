#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "event.hpp"
#include "routing-result.hpp"

size_t write_callback(
    char* data,
    size_t size,
    size_t nmemb,
    void* userdata

){
    std::string* response = static_cast<std::string*>(userdata);
    size_t byte_count = size * nmemb;
    response->append(data, byte_count);
    return byte_count;
}



std::string finnhub_client(){
    
    std::string response = "";
    long http_status = 0;


    const char* finnhub = std::getenv("FINNHUB_FREE_API");
    if(finnhub == nullptr) {
        std::cerr<<"Incorrect or missing FINNHUB API KEY"<<'\n';
        throw std::runtime_error("incorrect or Missing Finnhub API key");
    }
    const std::string FINNHUB_BASE_URL = "https://finnhub.io/api/v1/news?category=general&token=";
    std::string final_url = FINNHUB_BASE_URL + finnhub;

    CURL* curl = curl_easy_init();
    if(curl == nullptr){
        throw std::runtime_error("curl initiation failed");
    }

    curl_easy_setopt(curl, CURLOPT_URL, final_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode result = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    curl_easy_cleanup(curl);

    if(result != CURLE_OK) std::cerr << curl_easy_strerror(result)<<'\n';

    if(http_status != 200 or result != CURLE_OK){
        throw std::runtime_error("error occured, either the http is NOT 200 OR the result was malformed");
    }

    return response;
}