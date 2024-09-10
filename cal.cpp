#include "cal.h"
#include <iostream>

int Cal::mult(int par1, int par2){
    int i = par1 < par2 ? par1:par2;
    int j = par1 > par2 ? par1:par2;
    int value = 0;
    for(; i > 0; i--){
        value+= j;
    }
    saveValue += value;
    std::cout << " saveValue: " <<saveValue<< std::endl;
    return value;
}

int div(){
    return 0;
}

int Dev::mult_s(int par1, int par2){
    int i = par1 < par2 ? par1:par2;
    int j = par1 > par2 ? par1:par2;
    int value = 0;
    for(; i > 0; i--){
        value+= j;
    }
    saveValue1 += value;
    std::cout << " saveValue1: " <<saveValue1<< std::endl;
    return value;
}
