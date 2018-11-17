#ifndef __CDS_SIMULATOR_H
#define __CDS_SIMULATOR_H
#include <istream>
#include<string>
#include <vector>
#include<algorithm>
#include "price_bar.hpp"
#include "trade.hpp"
#include "trading_strategy.hpp"
#include <cmath>

namespace csis3700 {
  class simulator {
  public:
    /**
     * Create a simulator that makes trading decisions using the
     * supplied trading strategy.  The simulator will start the
     * account with the specified balance of cash.
     */
    simulator(trading_strategy* s, double balance){
        strategy = s;
        cash = balance;
        shares_held=0;
        last_price=0;
    }

    /**
     * Read price_bars from the supplied stream.  Note that the first
     * line of the stream will be a header and should be ignored.
     * Subsequent lines will be formatted:
     *   date/time open high low close volume adjusted_close
     *
     * Data in the stream will be in reverse chronological order.
     *
     * This method should populate the bars collection with bars
     * created from the contents of this stream.
     *
     * If reverse is true, the stream is in reverse chronological
     * order (in which case you must reverse the order of the data
     * when placing it in your bars collection).  If reverse if false,
     * the data is in chronological order.
     *
     */
    void read_bars(std::istream& is, bool reverse){
       std:: string date;
        double open, high, low, close, adjusted_close, volume;
          std:: string bug1,bug2,bug3,bug4,bug5,bug6,bug7,bug8;
           is >> bug1>>bug2>>bug3>>bug4>>bug5>>bug6>>bug7>>bug8;
        
        while(is>> date>>open>>high>>low>>close>>volume>>adjusted_close){
               
           bars.push_back(price_bar(date,open,high,low,close,adjusted_close,volume));
        
        }
        if (reverse){
           std:: reverse(bars.begin(),bars.end());
        }
    }

    /**
     * Perform the simulation by iterating through each bar with the
     * following steps:
     *    
     * 1) tell the strategy to process the bar 
     *
     * 2) ask the strategy how many shares it wants to trade
     *
     * 3) if there is enough cash in the account and the trade matches the
     *    current position (cannot sell more than you are holding)
     *   3a) create a trade object,
     *   3b) inform that strategy (trade_executed()) that a trade was executed,
     *   3c) update the cash available,
     *   3d) add the trade to the trades collection
     *
     */
    void run(){
        for(price_bar b : bars){
            last_price=b.get_adjusted_close();
            int items_to_trade=0;
            strategy->process_bar(b);
            items_to_trade=strategy->quantity_to_trade(cash);
             if(items_to_trade >0){
            trade t(b.get_date_time(),last_price,items_to_trade,true);
            shares_held+=items_to_trade;
            if(items_to_trade*last_price<cash){
            strategy->executed(t);
            cash-=items_to_trade*last_price;
             trades.push_back(t);
            }
            else {
                strategy->rejected(t);
            }
            }
             else if (items_to_trade <0){ 
                 trade t(b.get_date_time(),last_price,  abs (items_to_trade),false);
              if(abs(items_to_trade) <=shares_held){
                 strategy->executed(t);
            cash+=last_price*abs(items_to_trade);
            trades.push_back(t);
            shares_held+=items_to_trade;
            }
           else 
                strategy->rejected(t);
               
        }
        }
    }
    

    std::vector<trade> get_trades() const { return trades; }

    /**
     * Return the current account equity (cash plus holdings value).
     */
    double get_equity() const{
        return cash+last_price*shares_held;
    }

    /**
     * Return the number of shares held by this trading strategy.
     */
    double get_shares_held() const{
        return shares_held;
    }

    
    std::vector<price_bar> get_bars() const { return bars; }

    
  private:
    trading_strategy* strategy;
    double cash;
    std::vector<price_bar> bars;
    std::vector<trade> trades;
    int shares_held;
    double last_price;
  };
}

#endif
