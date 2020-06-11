//
// Created by isnob on 14/05/2020.
//

#ifndef LAB1_DURATIONLOGGER_H
#define LAB1_DURATIONLOGGER_H


#include <string>
#include <chrono>


class DurationLogger {
    std::string name;
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;

public:
    DurationLogger(const std::string &name);

    ~DurationLogger() ;
};

#endif //LAB1_DURATIONLOGGER_H
