#pragma once
#include <string>
#include <cstdint>


struct FinancialEvent{
    std::int64_t id;
    std::string source;
    std::string headline;
    std::string related;
    std::string summary;
    std::string category;
    std::string url;
    std::int64_t published_at;
    std::int64_t received_at;

// category: News category.

//  datetime: Published time in UNIX timestamp.

//  headline: News headline.

//  id: News ID. This value can be used for minId params to get the latest news only.

//  related: Related stocks and companies mentioned in the article.

//  source: News source.

//  summary: News summary.

//  url: URL of the original article.


};
