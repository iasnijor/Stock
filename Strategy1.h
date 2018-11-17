/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Strategy1.h
 * Author: Rojen
 *
 * Created on April 11, 2018, 12:15 AM
 */
#include"trading_strategy.hpp"
#include <cassert>
#ifndef STRATEGY1_H
#define STRATEGY1_H
namespace csis3700 {
    class strategy1 :public  trading_strategy{
    private : int days;
    int shares_held;
    public :
        strategy1(){
            days=0;
            shares_held=0;
        }
         void process_bar(const price_bar& b){
             if (days==20) {
                 days=0;
             }
             days++;
             
         }
           int quantity_to_trade(double cash) const {
               if (days==10){ 
                   return 20;
               }
               else if(days==20){return -(shares_held-10);
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


#endif /* STRATEGY1_H */

















