#pragma once
#include <string>
#include <vector>
#include "simulation.h"
struct DrawoutStats
{
	double peakAtDrawout{};
	double troughAtDrawout{};
	std::string peakDate{};
	std::string troughDate{};
};

struct WinRateStats
{
	int numWin{};
	int numLoss{};
	std::size_t totalTrades{};
};

void printWinRateStats(const WinRateStats&);
WinRateStats getWinRateStats(const SimulationResult&);
void printDrawoutStats(const DrawoutStats&);
DrawoutStats getMaxDrawoutStats(const SimulationResult&);
void printReturnStats(const SimulationResult&);
double getReturnPercentage(const SimulationResult&);
void printStats(const SimulationResult&);

