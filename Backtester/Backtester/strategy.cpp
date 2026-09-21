#include<iostream>
#include <vector>
#include "data.h"

int getShortWindow()
{
	std::cout << "Enter the short window size: ";
	int window{};
	std::cin >> window;
	return window;
}

int getLongWindow()
{
	std::cout << "Enter the long window size: ";
	int window{};
	std::cin >> window;
	return window;
}

std::vector<double> getMovingAverage(const std::vector<PriceRecord>& pricingData, const int window)
{
	std::vector<double> movingAverage{};
	double total{};
	for (std::size_t i{}; i < pricingData.size(); i++)
	{
		if (i < window-1)
		{
			total += pricingData[i].close;
			movingAverage.push_back(0.0);
		}
		else
		{
			if (i == window - 1)
				total = total + pricingData[i].close;
			else
				total = total - pricingData[i - window].close + pricingData[i].close;
			
			movingAverage.push_back(total / static_cast<double>(window));
		}
	}
	return movingAverage;
}

