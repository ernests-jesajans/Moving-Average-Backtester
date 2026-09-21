#pragma once
#include "data.h"
#include <vector>

struct PortfolioState
{
	std::string date{};
	double cash{};
	double units{};
	double value{};
};

struct TradeResult
{
	std::string entryDate{};
	double entryPrice{};
	std::string exitDate{};
	double exitPrice{};
};

struct SimulationResult
{
	std::vector<PortfolioState> portfolioStateData{};
	std::vector<TradeResult> tradeResultData{};
};

double getStartingCash();

SimulationResult getMASimulationData(const std::vector<double>&,
	const std::vector<double>&,
	const std::vector<PriceRecord>&,
	const double);

SimulationResult getBuyAndHoldSimulationData(const std::vector<PriceRecord>&, const double);
