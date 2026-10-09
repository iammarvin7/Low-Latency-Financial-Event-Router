#include <iostream>
#include <cstdlib>
#include <curl/curl.h>
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

int main(){

    // CURL* curl = curl_easy_init();
    // if(curl == nullptr){
    //     std::cerr<<"curl initialisation failed" << '\n';
    //     return 1;
    // }

    // curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    // CURLcode result = curl_easy_perform(curl);
    // curl_easy_cleanup(curl);

    // if(result != CURLE_OK){
    //     std::cerr << curl_easy_strerror(result) << '\n';
    // }


    // const char* finnhub = std::getenv("FINNHUB_FREE_API");
    // if(finnhub == nullptr){
    //     std::cerr<<"finnhub key not found"<<std::endl;
    //     return 1;
    // }
    
    // std::string response = "";
    // response.append("Financial", 9);
    // response.append(" News", 5);
    // response.append(" Received", 9);
    // std::cout<<response<< " and " << response.size()<<std::endl;


    // std::string response = "";
    // CURL* curl = curl_easy_init();
    // if(curl == nullptr){
    //     std::cerr<<"curl initiation failed"<<'\n';
    //     return 1;
    // }

    // curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // CURLcode result = curl_easy_perform(curl);
    // curl_easy_cleanup(curl);
    // if(result != CURLE_OK){
    //     std::cerr<< curl_easy_strerror(result)<< '\n';
    // }
    // std::cout<<response.size()<<std::endl;
    // std::cout<<response.substr(0,100)<<std::endl;

    std::string response = "";
    long http_status = 0;


    const char* finnhub = std::getenv("FINNHUB_FREE_API");
    if(finnhub == nullptr) {
        std::cerr<<"Incorrect FINNHUB API KEY"<<'\n';
        return 1;
    }
    const std::string FINNHUB_BASE_URL = "https://finnhub.io/api/v1/news?category=general&token=";
    std::string final_url = FINNHUB_BASE_URL + finnhub;


    CURL* curl = curl_easy_init();
    if(curl == nullptr){
        std::cerr<<"curl initiation failed"<<'\n';
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, final_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    CURLcode result = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
    curl_easy_cleanup(curl);

    if(result != CURLE_OK) std::cerr << curl_easy_strerror(result)<<'\n';

    std::cout<<http_status<<'\n';
    std::cout<<response.size()<<'\n';
    std::cout<<response.substr(0,300)<<'\n';









}