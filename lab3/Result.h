//
// Created by isnob on 25/05/2020.
//

#ifndef LAB3_RESULT_H
#define LAB3_RESULT_H


#include <string>

template<typename T>
class Result{
    std::string key;
    T value;
public:
    Result() = default;
    Result(std::string key) :key(std::move(key)){}
    Result(std::string key, T value):key(std::move(key)),value(std::move(value)){}
    std::string getKey(){return key;}
    T getValue(){return value;}
};


#endif //LAB3_RESULT_H
