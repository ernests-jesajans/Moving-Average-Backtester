#pragma once
#include <vector>
#include "data.h"
int getShortWindow();
int getLongWindow();
std::vector<double> getMovingAverage(const std::vector<PriceRecord>&, int);