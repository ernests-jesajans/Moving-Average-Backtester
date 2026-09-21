#include "data.h"
#include <vector>
#include <string>
#include <iostream>
#include "simulation.h"

bool isBuySignal(const std::vector<double>& shortMA, const std::vector<double>& longMA,const size_t i)
{
	return shortMA[i] > longMA[i] && shortMA[i - 1] < longMA[i - 1];
}

bool isSellSignal(const std::vector<double>& shortMA, const std::vector<double>& longMA, const size_t i)
{
	return shortMA[i] < longMA[i] && shortMA[i - 1] > longMA[i - 1];
}

double getStartingCash()
{
	std::cout << "Enter starting cash for simulation: ";
	double startingCash{};
	std::cin >> startingCash;
	return startingCash;
}

SimulationResult getMASimulationData(const std::vector<double>& shortMA, 
									const std::vector<double>& longMA, 
									const std::vector<PriceRecord>& priceData,
									const double startingCash)
{
	SimulationResult simulationData{};
	double cash{ startingCash };
	double units{};
	double value{ startingCash };
	std::string entryDate{};
	double entryPrice{};

	for (std::size_t i{}; i < shortMA.size(); i++)
	{
		if (i > 0 && longMA[i] != 0 && longMA[i-1] != 0)
		{
			if (isBuySignal(shortMA,longMA,i) && cash !=0)
			{
				units = cash / priceData[i].close;
				cash = 0;
				entryDate = priceData[i].date;
				entryPrice = priceData[i].close;
			}
			if ((isSellSignal(shortMA, longMA, i) || i == shortMA.size() - 1) && cash == 0)
			{
				cash = units * priceData[i].close;
				units = 0;
				simulationData.tradeResultData.push_back({ entryDate,entryPrice,priceData[i].date,priceData[i].close });
			}

		}	
		value = units * priceData[i].close + cash;
		simulationData.portfolioStateData.push_back({ priceData[i].date,cash,units,value });
	}
	return simulationData;
}

SimulationResult getBuyAndHoldSimulationData(const std::vector<PriceRecord>& priceData, const double startingCash)
{
	SimulationResult simulationData{};
	double cash{ startingCash };
	double units{};
	double value{ startingCash };
	std::string entryDate{};
	double entryPrice{};

	for (std::size_t i{}; i < priceData.size(); i++)
	{
		if (i == 0)
		{
			units = cash / priceData[i].close;
			cash = 0;
			entryDate = priceData[i].date;
			entryPrice = priceData[i].close;
		}
		else if (i == priceData.size() - 1)
		{
			cash = units * priceData[i].close;
			units = 0;
			simulationData.tradeResultData.push_back({ entryDate,entryPrice,priceData[i].date,priceData[i].close });
		}
		value = units * priceData[i].close + cash;
		simulationData.portfolioStateData.push_back({ priceData[i].date,cash,units,value });
	}
	return simulationData;
}