#pragma once
#include <string>
#include <vector>
struct PriceRecord
{
	std::string date{};
	double close{};
};

struct DateRange
{
	std::string startDate{};
	std::string endDate{};
};

bool isFileNameValid(std::string);
std::string getFileName();
std::vector<PriceRecord> getPricingVector(const std::string&,const DateRange&);
DateRange getDateRange();