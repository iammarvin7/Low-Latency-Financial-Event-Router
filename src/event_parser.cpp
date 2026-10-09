#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "event.hpp"
#include "routing-result.hpp"


FinancialEvent Financial_Event_converter(const nlohmann::json &j){
    FinancialEvent event;
    // std::int64_t id;
    // std::string source;
    // std::string headline;
    // std::string related;
    // std::string summary;
    // std::string category;
    // std::string url;
    // std::int64_t published_at;
    // std::int64_t received_at;

    //REQUIRED FIELDS (require validation)
    //ID
    if(!j.contains("id") or !j["id"].is_number_integer()) {
        throw std::invalid_argument("Id is invalid");
    }
    event.id = j["id"];

    //SOURCE
    if(!j.contains("source") or !j["source"].is_string() or j["source"].get<std::string>().empty()){
        throw std::invalid_argument("Source is invalid");
    }
    event.source = j["source"];

    //HEADLINE
    if(!j.contains("headline") or !j["headline"].is_string() or j["headline"].get<std::string>().empty()){
        throw std::invalid_argument("Headline is invalid");
    }
    event.headline = j["headline"];
    
    //SUMMARY
    if(!j.contains("summary") or !j["summary"].is_string() or j["summary"].get<std::string>().empty()){
        std::cout<<j["summary"]<<std::endl;
        throw std::invalid_argument("Summary is invalid");
    } 
    event.summary = j["summary"];

    //PUBLISHED AT
    if(!j.contains("datetime") or !j["datetime"].is_number_integer()){
        throw std::invalid_argument("published_time is invalid");
    } 
    event.published_at = j["datetime"];


    //OPTIONAL FIELDS (dont require validations)

    //RELATED
    if(j.contains("related") and j["related"].is_string()) {
        event.related = j["related"];
    }
    
    //CATEGORY
    if(j.contains("category") and j["category"].is_string()){ 
        event.category = j["category"];
    }

    //URL
    if(j.contains("url") and j["url"].is_string()){ 
        event.url = j["url"];
    }    

    return event;
}
