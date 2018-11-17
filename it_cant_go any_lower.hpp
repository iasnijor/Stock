/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   it_cant_go any_lower.hpp
 * Author: Rojen
 *
 * Created on April 4, 2018, 8:08 PM
 */
#include <cassert>
#include "trade.hpp"
#include "price_bar.hpp"
#include "trading_strategy.hpp"
#ifndef IT_CANT_GO_ANY_LOWER_HPP
#define IT_CANT_GO_ANY_LOWER_HPP

namespace csis3700 {

    class it_cant_go_any_lower : public trading_strategy {
    private:
        int number_of_red_bars;
        int days, shares_held;
        double price;
           public:

        it_cant_go_any_lower() {
            number_of_red_bars = 0;
            days = 0;
            shares_held = 0;
            price = 0;
            
        }

        void process_bar(const price_bar& b) {
            price = b.get_adjusted_close();
             if(days==16){
                  days=0;
            }
            days+=1;
               if(number_of_red_bars==3){
               
                number_of_red_bars=0;
            }
            if (b.get_close() < b.get_open()) {
                number_of_red_bars += 1;
            }
            else
                number_of_red_bars = 0;
         
           
        }

        int quantity_to_trade(double cash) const {
           if (number_of_red_bars==3) {
                    return 2;
           } 
           if(days==16){
return -shares_held;   
           }
           return 0;
                            
            
        }

        void executed(const trade& t) {
            if(t.is_buy())shares_held+=t.get_quantity();
            else shares_held -= t.get_quantity();

        }
        void rejected(const trade& t) {
            assert(1 > 2);
        }
    };
}

#endif /* IT_CANT_GO_ANY_LOWER_HPP */










































