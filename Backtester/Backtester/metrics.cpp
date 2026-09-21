#include <vector>
#include <iostream>
#include <algorithm>
#include "simulation.h"
#include "metrics.h"
#include <iomanip>

double getReturnPercentage(const SimulationResult& simulationData)
{
	const PortfolioState& firstDay{ simulationData.portfolioStateData[0]};
	const PortfolioState& lastDay{ simulationData.portfolioStateData.back()};
	return ((lastDay.value - firstDay.value) / firstDay.value) * 100;
}

void printReturnStats(const SimulationResult& simulationData)
{
	const PortfolioState& firstDay{ simulationData.portfolioStateData[0] };
	const PortfolioState& lastDay{ simulationData.portfolioStateData.back() };
	std::cout << "Start date: " << firstDay.date << "  End date: " << lastDay.date << '\n'
		<< "Starting cash: " << firstDay.value << "  Ending cash: " << lastDay.value << '\n'
		<< "Return percentage: " << getReturnPercentage(simulationData) << "%\n";
}

DrawoutStats getMaxDrawoutStats(const SimulationResult& simulationData)
{
	const std::vector<PortfolioState>& arr{ simulationData.portfolioStateData };
	PortfolioState peakSoFar{ arr[0]};
	double troughAtMaxDrawout{};
	double maxDrawout{};
	double peakAtMaxDrawout{};
	std::string peakDate{};
	std::string troughDate{};
	for (std::size_t i{}; i < arr.size(); i++)
	{
		if (arr[i].value > peakSoFar.value)
		{
			peakSoFar = arr[i];
		}

		if (maxDrawout < peakSoFar.value - arr[i].value)
		{
			peakAtMaxDrawout = peakSoFar.value;
			troughAtMaxDrawout = arr[i].value;
			maxDrawout = peakSoFar.value - arr[i].value;
			peakDate = peakSoFar.date;
			troughDate = arr[i].date;
		}
	}
	return DrawoutStats{peakAtMaxDrawout,troughAtMaxDrawout,peakDate,troughDate};
}

void printDrawoutStats(const DrawoutStats& drawoutStats)
{
	std::cout << "Peak date at drawout: " << drawoutStats.peakDate << " Peak close at drawout: " << drawoutStats.peakAtDrawout << '\n' <<
		"Trough date at drawout: " << drawoutStats.troughDate << " Trough close at drawout: " << drawoutStats.troughAtDrawout << "\n"
		<< "Max drawout: " << drawoutStats.peakAtDrawout - drawoutStats.troughAtDrawout << '\n'
		<< "Drawout percentage: " << ((drawoutStats.peakAtDrawout - drawoutStats.troughAtDrawout) / drawoutStats.peakAtDrawout) * 100 << "% \n";

}

WinRateStats getWinRateStats(const SimulationResult& simulationData)
{
	int numWin{};
	int numLoss{};
	const std::size_t totalTrades{simulationData.tradeResultData.size()};
	for (auto trade : simulationData.tradeResultData)
	{
		if (trade.entryPrice < trade.exitPrice)
			numWin++;
		else if (trade.entryPrice > trade.exitPrice)
			numLoss++;
	}
	return { numWin,numLoss,totalTrades };
}

void printWinRateStats(const WinRateStats& winRateStats)
{
	std::cout << "Win rate percentage: " << (static_cast<double>(winRateStats.numWin) / static_cast<double>(winRateStats.totalTrades)) * 100 << "%\n"
		<< "Trades won: " << winRateStats.numWin << "  Trades lost: " << winRateStats.numLoss << '\n';
}

void printStats(const SimulationResult& simulationData)
{
	std::cout << std::fixed << std::setprecision(2);
	printReturnStats(simulationData);
	std::cout << '\n';
	printDrawoutStats(getMaxDrawoutStats(simulationData));
	std::cout << '\n';
	printWinRateStats(getWinRateStats(simulationData));
	std::cout << '\n';
}