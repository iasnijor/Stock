#ifndef __CDS_STRATEGY_H
#define __CDS_STRATEGY_H
#include "trade.hpp"
#include "price_bar.hpp"

namespace csis3700 {

  /**
   * This is the abstract trading_strategy class.  Your trading
   * strategies will be descendants of this class.
   */
  class trading_strategy {
  public:

    /**
     * Construct a new trading strategy.
     */
    trading_strategy() { }
    
    /**
     * The simulation sends this message to tell the trading strategy
     * about a new bar.  Each (simulated) day's bar is passed to this
     * strategy, one at a time, so that the strategy can make
     * decisions.
     */
    virtual void process_bar(const price_bar& b) = 0;

    /**
     * The simulation sends this message to ask the strategy how many
     * shares it wants to buy or sell.  Return the number of shares
     * this strategy wants to trade at the current price.  Positive
     * number is a buy, negative is a sell (0 for none, of course).
     * The current cash available for trading will be supplied as an
     * argument.
     */
    virtual int quantity_to_trade(double cash) const = 0;

    
    /**
     * Once a strategy has indicated that it wants to trade (buy or
     * sell, see methods above), the simulation will try to execute
     * this trade.  If the trade is successful, the strategy will be
     * notified by sending the executed message.  This is where you
     * could keep track of the number of shares held.
     */
    virtual void executed(const trade& t) = 0;

    /**
     * As with executed except this message is sent when a trade is
     * rejected (due to insufficient funds or short-selling).
     */
    virtual void rejected(const trade& t) = 0;

  };
}


#endif
