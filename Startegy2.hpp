/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Startegy2.hpp
 * Author: Rojen
 *
 * Created on April 11, 2018, 3:15 PM
 */

#ifndef STARTEGY2_HPP
#define STARTEGY2_HPP
#include"trading_strategy.hpp"
#include <cassert>

namespace csis3700 {
    class strategy2 :public  trading_strategy{
    private : int days,first_day;
                bool trading_day,buy;
                double shares_held;
               double close_price, initial_price;
    public :
        strategy2(){
            days=0;
            shares_held=0;
            close_price =0;
            initial_price=0;
            first_day=1;
            trading_day=false;
        }
         void process_bar(const price_bar& b){
           
             if(first_day==1) {
             initial_price=b.get_adjusted_close();
             first_day=0;
              }
             
               if (close_price>initial_price){
                   trading_day=true;
                   days=0;
                   first_day=1;
               }
             else {
                 trading_day= false;
                    }
             close_price=b.get_adjusted_close();
            
             days++;
             
         }
           int quantity_to_trade(double cash) const {
               if (days==1 && shares_held==0) return 20;
               if (trading_day) {
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




#endif /* STARTEGY2_HPP */


























