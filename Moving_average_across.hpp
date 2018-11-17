/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Moving_average_across.hpp
 * Author: Rojen
 *
 * Created on April 4, 2018, 8:09 PM
 */

#ifndef MOVING_AVERAGE_ACROSS_HPP
#define MOVING_AVERAGE_ACROSS_HPP
#include "trading_strategy.hpp"
#include <list>
#include"trade.hpp"
#include <iostream>
#include "price_bar.hpp"
#include <cassert>
namespace csis3700{
  class moving_average_across: public trading_strategy{
      
  private : std:: list<double> v1;
            std:: list<double> v2;
            double total1,total2,average_20,average_50,price;
               int shares_held,days;
  public :
      moving_average_across(){
          shares_held=0;
          total1=0;
          total2=0;
          average_20=0;
          average_50=0;
          days=0;
      }
   void process_bar(const price_bar& b){
       days++;
       v1.push_back(b.get_adjusted_close());
       v2.push_back(b.get_adjusted_close());
       if( v2.size()==20){
              for(double close1:v2){
               total1+=close1;
           }
           average_20=total1/20;
           total1=0;
            v2.pop_front();
       }
           if(v1.size()==50){
               for(double close2:v1){
                   total2+=close2;
               }
               average_50=total2/50;
               total2=0;
                v1.pop_front();
           }
       price=b.get_adjusted_close();
       }
    int quantity_to_trade(double cash) const{
       if(days>50){
       if(average_20>average_50) 
           if (cash/price>=10) return 10;
       else if(average_50>average_20) 
           return -shares_held;
       else return 0;
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

#endif /* MOVING_AVERAGE_ACROSS_HPP */








































