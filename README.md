# Moving Average Backtester

A small C++ project I built to test out a basic trading strategy (moving average
crossover) against historical stock data, and see how it stacks up against just
buying and holding. Mostly built as a way to reinforce my learning of C++  and use some features (structs, file I/O, STL containers) in practice while also getting into some basic quant/finance concepts.

## What it does

1. Reads historical daily price data from a CSV (currently set up for AAPL,
   sourced from Stooq).
2. Computes short and long moving averages over that data.
3. Runs a simple crossover strategy: buy when the short average crosses above
   the long one, sell when it crosses back below.
4. Also runs a buy-and-hold "strategy" on the same data as a baseline comparison.
5. Prints out stats for both: total return, max drawdown, and win rate.

Example output looks like:

```
------MA CROSSOVER STRATEGY------
Start date: 20130102  End date: 20161230
Starting cash: 10000.00  Ending cash: 16856.07
Return percentage: 68.56%
...
------BUY AND HOLD STRATEGY------
...
```

## Design decisions (and the tradeoffs I know about)

A few things I deliberately kept simple for this first version, rather than
things I just didn't think about:

- **All in, all out position sizing**, every buy converts 100% of cash into
  units, every sell converts 100% back to cash.
- **Trades execute at the signal day's closing price**, not the next day's
  open. This is a known simplification but a more realistic version would trade at the next   	    available price instead.
- **Any position still open at the end of the data gets force closed** at the
  last available price, so total return is always a complete number.
- **No transaction costs modeled.** Trading has fees and
  price impact, so real-world performance would be somewhat worse than what's reported here.

## Known limitations / what I'd add next

- Currently the file name, date range, cash, and window sizes are hardcoded
  in `main.cpp` (see the `config` namespace) rather than taken as command
  line arguments or interactive prompts.
- Sharpe ratio isn't computed yet.
- The buy-and-hold and moving-average simulations share a decent chunk of
  logic (the day-by-day portfolio bookkeeping) that could be factored out
  instead of duplicated.
- Only one strategy (MA crossover) is implemented beyond the buy and hold
  baseline. Would like to add a mean-reversion strategy for a more
  interesting comparison, and eventually make strategies swappable via
  polymorphism (when learnt) instead of separate functions.

## Project structure

- `data.h` / `data.cpp` — CSV parsing, date range filtering
- `strategy.h` / `strategy.cpp` — moving average calculation
- `simulation.h` / `simulation.cpp` — the actual day-by-day simulation loop,
  `PortfolioState` / `TradeResult` / `SimulationResult` structs
- `metrics.h` / `metrics.cpp` — computing and printing return / drawdown / win rate
- `main.cpp` — wires it all together

## Running it

Needs a C++ compiler with at least C++17 (uses CTAD in a couple of spots).
Drop a Stooq-format CSV (ticker.us.txt) in the working directory, update the
`config` namespace in `main.cpp` if you want different settings, build, run.

Data source: [Stooq](https://stooq.com) — free historical daily price data.
