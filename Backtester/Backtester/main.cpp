#include <iostream>
#include <vector>
#include "data.h"
#include "strategy.h"
#include "simulation.h"
#include "metrics.h"

namespace config
{
    const DateRange dateRange{ "20230101","20260101" };
    constexpr double startingCash{ 10000 };
    constexpr int shortWindow{9};
    constexpr int longWindow{21};
    const std::string fileName{ "aapl.us.txt" };
}

std::string getValidFileName()
{
    std::string fileName{};
    do
    {
        fileName = getFileName();
    } while (!isFileNameValid(fileName));
    return fileName;
}

void printAllStats(const SimulationResult& MAsimulationData,
    const SimulationResult& buyAndHoldsimulationData)
{
    std::cout << "------MA CROSSOVER STRATEGY------ \n";
    printStats(MAsimulationData);
    std::cout << "------BUY AND HOLD STRATEGY------ \n";
    printStats(buyAndHoldsimulationData);
}
int main()
{

   
    std::vector<PriceRecord> priceData{ getPricingVector(config::fileName,config::dateRange) };

    if (priceData.empty())
    {
        std::cerr << "No price data found for the given date range.\n";
        return 1;
    }
    const std::vector<double> shortMA{ getMovingAverage(priceData,config::shortWindow) };
    const std::vector<double> longMA{ getMovingAverage(priceData,config::longWindow) };
    const SimulationResult MAsimulationData{ getMASimulationData(shortMA,longMA,priceData,config::startingCash) };
    const SimulationResult buyAndHoldsimulationData{ getBuyAndHoldSimulationData(priceData,config::startingCash) };
    printAllStats(MAsimulationData, buyAndHoldsimulationData);
    return 0;
}
