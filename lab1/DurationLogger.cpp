//
// Created by isnob on 14/05/2020.
//

#include <iostream>
#include "DurationLogger.h"
#include <time.h>
#include <chrono>
DurationLogger::DurationLogger(const std::string& name):name(name) { //da implementare

    start=std::chrono::high_resolution_clock::now();
    std::cout<< " >>>>>>>>>>>>>> starting ["<<name<<"]"<<std::endl;

}

DurationLogger::~DurationLogger() { //da implementare
    end=std::chrono::high_resolution_clock::now();

    std::chrono::duration time=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"<<<<<<<<<<<<<<< ending ["<<name<<" : duration "<<time.count()<<" ms] "<<std::endl;
}