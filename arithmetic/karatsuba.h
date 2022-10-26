//
// Created by L Su on 26/8/2022.
//

#ifndef ARITHMETIC_KARATSUBA_H
#define ARITHMETIC_KARATSUBA_H
#include<string>
#include<vector>
#include<math.h>
#include <iostream>
using namespace std;

class karatsuba{
public:
    karatsuba()=default;
    ~karatsuba()=default;
    string addition(string str1,string str2,int base);
    string subtraction(string str1,string str2, int base);
    string multiplication(string str1, string str2, int base);
    string removeZero(string str);

};
#endif //ARITHMETIC_KARATSUBA_H
