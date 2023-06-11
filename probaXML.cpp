#include <iostream>
#include "ReadingXML.hpp"

int main() {
    ReadingXML readingXml;  // Create an instance of the ReadingXML class

    std::cout << readingXml.getStartingTime() << std::endl;  // Call the getStartingTime() member function
    std::cout << readingXml.getStep() << std::endl;
    std::cout << readingXml.getOde() << std::endl;
    std::cout << readingXml.getSystemInput() << std::endl;
    for(double i : readingXml.getInitCond())
        std::cout << i << std::endl;

    return 0;
}