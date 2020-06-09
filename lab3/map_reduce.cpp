//
// Created by isnob on 28/05/2020.
//
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <regex>
template<typename MapperInputT, typename ResultT, typename ReducerInputT, typename M, typename R>
std::map<std::string, ResultT> mapreduce(const std::string &inputf, M &mapfun, R &reducefun) {
    std::string line;
    std::map<std::string, ResultT> results;

    std::ifstream ifs(inputf);

    if (!ifs.is_open()) {
        std::cout << "unable to open file" << std::endl;
    }

    while (getline(ifs, line)) {
        std::vector<ResultT> m_results = mapfun(MapperInputT(line));
        for (auto r: m_results) {
            auto it = results.find(r.getKey());

            ResultT acc = it == results.end() ? ResultT(r.getKey(),0) : it->second;

            ResultT new_acc = reducefun(ReducerInputT(r.getKey(), r.getValue(), acc.getValue()));
            results[new_acc.getKey()] = new_acc;
        }
    }

    return results;
}