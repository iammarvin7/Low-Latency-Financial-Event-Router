#pragma once
#include <string>


struct RoutingResult{
    std::string route;
    double confidence;
    std::string decision_engine;
    double decision_latency_ms;
    double total_latency_ms;
    std::string status;
};