/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Rojen
 *
 * Created on April 4, 2018, 6:34 PM
 */

#include <cstdlib>
#include <fstream>
#include "Moving_average_across.hpp"
#include"it_cant_go any_lower.hpp"
#include"simulator.hpp"
#include"price_bar.hpp"
#include"trade.hpp"
#include"trading_strategy.hpp"

#include "Strategy1.hpp"
#include "Startegy2.hpp"
using namespace std;
using namespace csis3700;
#include<iostream>
/*
 * 
 */
int main(int argc, char** argv) {
    ifstream ins;
    int cash=100000;
    
    ins.open("aapl.dat");
    if(!(ins.is_open())) return 0;
    it_cant_go_any_lower  it;
    strategy1 s1;
    strategy2 s2;
    moving_average_across m;
    trading_strategy *ts=&m;
    simulator s( ts,cash);
   
    s.read_bars(ins,true);
    s.run();
  std::vector<trade> trades=s.get_trades();
   std::vector<price_bar> bars= s.get_bars();

   price_bar front = bars.front();
   price_bar back = bars.back();
    
    cout << "DATA File:"<< "data/appe.dat"<< endl;
    cout <<"Start Date :"<<front.get_date_time()<<endl;
    cout << "End Date :"<< back.get_date_time()<< endl;
    cout << "Bars :"<< bars.size()<< endl;
    cout << "Trades :" << trades.size()<< endl;
   cout << "Initial Equity:"<< cash<<endl;
    cout <<"Final Equity :"<< s.get_equity()<<endl;;
    cout <<"Profit Percent :" << (s.get_equity()-cash)/cash<<endl;
    return 0;
}
































































