//
// Created by isnob on 25/05/2020.
//

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#ifndef LAB3_MAPPERINPUT_H
#define LAB3_MAPPERINPUT_H

#endif //LAB3_MAPPERINPUT_H


class MapperInput{
    std::string line;
public:
    MapperInput(std::string line):line(std::move(line)){}
    std::string getLine() {return line;}
    std::vector<char> toJson() const{
        boost::property_tree::ptree tree;
        tree.put("1",line);
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
        line = pt.get<std::string>("1");
    }
};