//
// Created by isnob on 25/05/2020.
//

#include <string>

#ifndef LAB3_REDUCERINPUT_H
#define LAB3_REDUCERINPUT_H

#endif //LAB3_REDUCERINPUT_H
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
template<typename V, typename A>
class ReducerInput {
    std::string key;
    V value;
    A accumulator;
public:
    ReducerInput(std::string key, V value, A accumulator):key(std::move(key)),value(std::move(value)), accumulator(std::move(accumulator)){}
    std::string getKey(){return key;}
    V getValue(){return value;}
    A getAccumulator(){ return  accumulator;}

    std::vector<char> toJson() const{
        boost::property_tree::ptree tree;
        tree.put("key",key);
        tree.put("value",value);
        tree.put("accumulator",accumulator);
        std::ostringstream buf;
        boost::property_tree::write_json(buf, tree, false);
        std::vector<char> result;
        std::string s = buf.str();
        std::copy(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }
    void fromJson(std::shared_ptr<char[]> ptr) {
        std::cout<<ptr<<" - "<<std::endl;
        boost::property_tree::ptree pt;
        std::stringstream buf;
        buf << ptr;
        boost::property_tree::read_json(buf, pt);
        key = pt.get<std::string>("1");
    }
};