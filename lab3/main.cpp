#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <vector>
#include <map>
#include <regex>
#include "Result.h"
#include "MapperInput.h"
#include "ReducerInput.h"
#include "DurationLogger.h"
#include "map_reduce_regex.cpp"


std::string getOsName();


template<typename MapperInputT, typename ResultT>
std::vector<ResultT> map_ip(MapperInputT input) {
    std::smatch ip_match;
    std::string line = input.getLine();
    std::regex_search(line, ip_match, std::regex("^[^ ]+"));
    return std::vector<ResultT>{ResultT(ip_match[0], 1)};
}

template<typename MapperInputT, typename ResultT>
std::vector<ResultT> map_regex_ip(MapperInputT input, const std::regex &regex) {
    std::smatch ip_match;
    std::string line = input.getLine();
    std::regex_search(line, ip_match, regex);
    return std::vector<ResultT>{ResultT(ip_match[0], 1)};
}

template<typename MapperInputT, typename ResultT>
std::vector<ResultT> map_regex_hour(MapperInputT input, const std::regex &regex) {
    std::smatch ip_match;
    std::string line = input.getLine();
    std::regex_search(line, ip_match, regex);
    return std::vector<ResultT>{ResultT(ip_match[1], 1)};
}

template<typename MapperInputT, typename ResultT>
std::vector<ResultT> map_regex_url(MapperInputT input, const std::regex &regex) {
    std::smatch ip_match;
    std::string line = input.getLine();
    std::regex_search(line, ip_match, regex);
    return std::vector<ResultT>{ResultT(ip_match[2], 1)};
}
template<typename MapperInputT, typename ResultT>
std::vector<ResultT> map_regex_ip_status(MapperInputT input, const std::regex &regex) {
    std::smatch ip_match;
    std::string line = input.getLine();
    std::regex_search(line, ip_match, regex);
    return std::vector<ResultT>{ResultT(ip_match[3].str()+"_"+ip_match[1].str(), 1)};
}




template<typename ReducerInput, typename ResultT>
ResultT reduce(ReducerInput input) {
    return ResultT(input.getKey(), input.getValue() + input.getAccumulator());
}





int main() {
    auto *ip_regex = new std::regex("^[^ ]+");
    auto *hour_regex = new std::regex("[0-9]{2}\\/[a-zA-Z]{3}\\/[0-9]{4}:([0-9]{2})");
    auto *multi_regex = new std::regex("(^[^ ]+).*\".* (.*) .*\" ([0-9]{3})");
    // group 1 ip
    // group 2 url
    // group 3 status

    std::cout << "Hello, World! " << getOsName() << std::endl;
   /*{
        DurationLogger dl("Simple reducer");
        using ResultT = Result<int>;
        using ReducerInputT = ReducerInput<int, int>;

        auto results = map_reduce_regex<MapperInput, ResultT, ReducerInputT>(
                "../logs.txt",
                map_regex_ip<MapperInput, ResultT>,
                reduce<ReducerInputT, ResultT>,*ip_regex);

        for (auto &x: results) {
            std::cout << x.first << ": " << x.second.getValue() << std::endl;
        }
        std::cout <<"#"<< results.size() << std::endl;
    }*/
    {
        DurationLogger dl("Hour reducer");
        using ResultT = Result<int>;
        using ReducerInputT = ReducerInput<int, int>;

        auto results = map_reduce_regex<MapperInput, ResultT, ReducerInputT>(
                "../logs.txt",
                map_regex_hour<MapperInput, ResultT>,
                reduce<ReducerInputT, ResultT>, *hour_regex);

        for (auto &x: results) {
            std::cout << x.first << ": " << x.second.getValue() << std::endl;
        }
        std::cout << "#"<< results.size() << std::endl;
    }
    {
        DurationLogger dl("Most visited url");
        using ResultT = Result<int>;
        using ReducerInputT = ReducerInput<int, int>;

        auto results = map_reduce_regex<MapperInput, ResultT, ReducerInputT>(
                "../logs.txt",
                map_regex_url<MapperInput, ResultT>,
                reduce<ReducerInputT, ResultT>, *multi_regex);

        for (auto &x: results) {
            std::cout << x.first << ": " << x.second.getValue() << std::endl;
        }
        std::cout << "#"<< results.size() << std::endl;
    }
/*
    {
            DurationLogger dl("Status code");
            using ResultT = Result<int>;
            using ReducerInputT = ReducerInput<int, int>;

            auto results = map_reduce_regex<MapperInput, ResultT, ReducerInputT>(
            "../logs.txt",
            map_regex_ip_status<MapperInput, ResultT>,
            reduce_ip<ReducerInputT, ResultT>, *multi_regex);

            for (auto &x: results) {
                if(x.first.starts_with("400")||x.first.starts_with("404")||x.first.starts_with("405"))
                    std::cout << x.first << ": " << x.second.getValue() << std::endl;
            }
            std::cout << "#"<< results.size() << std::endl;
    }*/

    return 0;
}

std::string getOsName() {
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
}