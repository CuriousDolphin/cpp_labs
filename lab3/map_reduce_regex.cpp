//
// Created by isnob on 28/05/2020.
//

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <regex>
template<typename MapperInputT, typename ResultT, typename ReducerInputT, typename M, typename R>
std::map<std::string, ResultT>
map_reduce_regex(const std::string &inputf, M &mapfun, R &reducefun, const std::regex &regex) {
    std::string line;
    std::map<std::string, ResultT> results;

    std::ifstream ifs(inputf);

    if (!ifs.is_open()) {
        std::cout << "unable to open file" << std::endl;
    }

    while (getline(ifs, line)) {
        std::vector<ResultT> m_results = mapfun(MapperInputT(line), regex);
        for (auto r: m_results) {
            auto it = results.find(r.getKey());
            //std::cout<<"key "<<r.getKey()<<" Value "<<r.getValue()<<std::endl;

            // ResultT acc = it == results.end() ? ResultT(r.getKey()) : it->second;
            ResultT acc = it == results.end() ? ResultT(r.getKey(),0) : it->second;

            ResultT new_acc = reducefun(ReducerInputT(r.getKey(), r.getValue(), acc.getValue()));
            results[new_acc.getKey()] = new_acc;
        }
    }

    return results;
}
