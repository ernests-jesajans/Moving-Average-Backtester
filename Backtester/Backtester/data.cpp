#include <iostream>
#include <fstream>
#include <vector>
#include <string_view>
#include "data.h"
#include <sstream>

namespace csvColumns
{
	constexpr int dateColumn{ 3 };
	constexpr int closeColumn{ 8 };
}

std::string getFileName()
{
	std::cout << "Enter market data file name: ";
	std::string fileName{};
	std::cin >> fileName;
	fileName = fileName + ".txt";
	return fileName;
}

bool isFileNameValid(std::string fileName)
{
	std::ifstream fileStream{ fileName };
	if (!fileStream.is_open()) 
	{
		std::cout << "Failed to open file\n";
		return false;
	}
	fileStream.close();
	return true;
}

DateRange getDateRange()
{
	std::cout << "(Type 0 for no date)" << '\n' << "Enter start date and end date (YYYYMMDD): ";
	std::string startDate{};
	std::string endDate{};
	std::cin >> startDate >> endDate;
	return { startDate,endDate };
}

std::vector<PriceRecord> getPricingVector(const std::string& fileName,const DateRange& dateRange)
{
	std::ifstream fileStream{ fileName };
	bool startReading{ false };
	std::string line{};
	std::vector<PriceRecord> pricingData{};
	bool isFirstRow{ true };

	while (std::getline(fileStream, line))
	{
		int column{};
		std::string date{};
		double close{};
		std::stringstream ss{ line };
		std::string data{};

		while (std::getline(ss, data, ','))
		{
			if (!isFirstRow)
			{
				column++;
				if (column == csvColumns::dateColumn)
				{
					date = data;
				}
				else if (column == csvColumns::closeColumn)
				{
					close = std::stod(data);
				}
			}

		}
		isFirstRow = false;
		bool afterStart{ dateRange.startDate == "0" || date >= dateRange.startDate };
		bool beforeEnd{ dateRange.endDate == "0" || date <= dateRange.endDate };

		if (afterStart && beforeEnd)
		{
			pricingData.push_back(PriceRecord{ date, close });
		}
		
		
	}

	return pricingData;
}

