/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Calculator.cpp
 * Author: Rojen
 *
 * Created on March 27, 2018, 6:18 PM
 */
#include"infix_evaluator.h"
#include"tokenizer.h"
#include<iostream>
#include <cstdlib>
using namespace csis3700;
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    tokenizer t;
    infix_evaluator i;
    queue<token> infix;
    cout << "Enter expression : ";
    infix = t.tokenize(cin);
    double answer = i.evaluate(infix);
    cout << "Answer: " << answer;
    return 0;
}







