#pragma once
#include <nlohmann/json.hpp>
#include "event.hpp"

FinancialEvent Financial_Event_converter(const nlohmann::json& j);