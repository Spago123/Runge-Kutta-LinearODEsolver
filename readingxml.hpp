#ifndef READINGXML_HPP
#define READINGXML_HPP

#include <string>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
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

    double getStartTime(){
        return std::stod(rootNode->first_node("startTime")->value());
    }

    double getStopTime(){
        return std::stod(rootNode->first_node("stopTime")->value());
    }

    double getStep(){
        return std::stod(rootNode->first_node("deltaT")->value());
    }

    std::string getOde(){
        return rootNode->first_node("equation")->value();
    }

    std::string getFile(){
        return rootNode->first_node("file")->value();
    }

    std::string getSystemInput(){
        return rootNode->first_node("U")->value();
    }

    Eigen::MatrixXd getInitCond(){
        std::vector<double> initCond;
        rapidxml::xml_node<>* initialConditions = rootNode->first_node("initialConditions");

        for (rapidxml::xml_node<>* conditions = initialConditions->first_node(); conditions; conditions = conditions->next_sibling()){
            initCond.push_back(std::stod(conditions->value()));
        }

        Eigen::MatrixXd initCond_(initCond.size(), 1);
        for(int i = 0; i < initCond.size(); i++)
            initCond_(i, 0) = initCond[i];

        return initCond_;
    }
};

#endif
