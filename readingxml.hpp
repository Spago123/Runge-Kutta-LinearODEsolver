#ifndef READINGXML_HPP
#define READINGXML_HPP

#include <string>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"

class ReadingXML{
    rapidxml::xml_node<>* rootNode;
    public:
    ReadingXML(){
        std::ifstream file("data.xml");
        std::string xmlContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        rapidxml::xml_document<> doc;
        doc.parse<0>(&xmlContent[0]);
        rootNode = doc.first_node("ODE");
    }

    double getStartingTime(){
        return std::stod(rootNode->first_node("t0")->value());
    }

    double getStep(){
        return std::stod(rootNode->first_node("deltaT")->value());
    }

    std::string getOde(){
        return rootNode->first_node("equation")->value();
    }

    std::string getSystemInput(){
        return rootNode->first_node("U")->value();
    }

    std::vector<double> getInitCond(){
        std::vector<double> initCond;
        rapidxml::xml_node<>* initialConditions = rootNode->first_node("initialConditions");

        for (rapidxml::xml_node<>* conditions = initialConditions->first_node(); conditions; conditions = conditions->next_sibling()){
            initCond.push_back(std::stod(conditions->value()));
        }

        return initCond;
    }
};

#endif
