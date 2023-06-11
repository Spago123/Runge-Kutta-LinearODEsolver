#include <iostream>
#include "ReadingXML.hpp"

int main() {
    ReadingXML readingXml;  // Create an instance of the ReadingXML class

    std::cout << readingXml.getStartTime() << std::endl;  // Call the getStartingTime() member function
    std::cout <<readingXml.getStopTime() << std::endl;
    std::cout << readingXml.getStep() << std::endl;
    std::cout << readingXml.getOde() << std::endl;
    std::cout << readingXml.getSystemInput() << std::endl;
    std::cout << readingXml.getInitCond() << std::endl;
    std::cout << readingXml.getFile() << std::endl;

    return 0;
}