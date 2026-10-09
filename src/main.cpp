#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "event_parser.hpp"
#include "finnhub_client.hpp"
#include "event.hpp"



int main(){

    try{
        std::string response = finnhub_client();
        nlohmann::json j = nlohmann::json::parse(response);
        if(j.is_array() and !j.empty()){
            std::vector<FinancialEvent> events;
            FinancialEvent event;
            int failed = 0;
            for(int i = 0; i < j.size(); ++i){
                try{
                    event = Financial_Event_converter(j[i]);
                    events.push_back(event);
                }
                catch(const std::invalid_argument& e){
                    failed++;
                    std::cerr<<e.what()<<std::endl;
                }
            }
            std::cout<<"Articles received: "<<j.size()<<std::endl;
            std::cout<<"Articles processes: "<<events.size()<<std::endl;
            std::cout<<"Articles rejected: "<<failed<<std::endl;
            if(!events.empty()){    
                std::cout<<"First headline: "<<events.front().headline<<std::endl;
                std::cout<<"Last headline: "<<events.back().headline<<std::endl;
            }
        }
    }
    catch(const nlohmann::json::parse_error& e){
        std::cerr<<"Json parsing error: "<<e.what() <<std::endl;
        return 1;
    }
    catch(const std::runtime_error& e){
        std::cerr<<"Finnhub client runtime error: "<< e.what() << std::endl;
        return 1;
    }



    // std::cout<<http_status<<'\n';
    // std::cout<<response.size()<<'\n';
    // std::cout<<response.substr(0,300)<<'\n';



    


    // *** TESTS ***
    //
    //TEST - 0
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


    // TEST - 1 : malformed json
    // try{
    //     nlohmann::json j = nlohmann::json::parse(R"({"headline": "Apple announces a new product")");
                                                    // *                                           *
    //     if(j.is_array() and !j.empty()){
    //         std::string first_headline = j[0]["headline"].get<std::string>();
    //         std::cout<<first_headline<<std::endl;
    //     }
    // }
    // catch(const nlohmann::json::parse_error& e){
    //     std::cerr<<"Json parsing error: "<<e.what() <<std::endl;
    // } 
    // ===> ERROR WILL BE GENERATED: "Json parsing error: [json.exception.parse_error.101] parse error at line 1, column 45: syntax error while parsing object - unexpected end of input; expected '}"   
    // std::cout<<res<<std::endl;
    // std::cout<<j.size()<<std::endl;
    // for(int i = 0; i < 10; ++i){
    //     std::cout<<j[i]["headline"]<<std::endl;
    // }


    //TEST - 2: invalid input article data
    // const std::string test_response = R"([
    //     {
    //         "id": 101,
    //         "headline": "Nvidia announces record quarterly revenue",
    //         "source": "Reuters",
    //         "summary": "Nvidia reports higher revenue driven by AI demand.",
    //         "datetime": 1791500000,
    //         "category": "business",
    //         "related": "NVDA",
    //         "url": "https://example.com/news/101"
    //     },
    //     {
    //         "id": 102,
    //         "headline": 404,
    //         "source": "Bloomberg",
    //         "summary": "A financial news article.",
    //         "datetime": 1791500100
    //     },
    //     {
    //         "id": 103,
    //         "source": "CNBC",
    //         "summary": "Another financial news article.",
    //         "datetime": 1791500200
    //     }
    // ])";

}