#include <fstream>
#include <string>
#include <sstream> 
#include <iterator>
#include "type.h"



//* FUNZIONE PER LEGGERE I PARAMETRI DA FILE *//
Parameters readFileToVector(const std::string& filename)
{
	Parameters param;
    std::ifstream source;
    source.open(filename);
    std::vector<std::string> lines;
    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(source, line))
    {
    	std::istringstream iss(line);
        tokens = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        lines.push_back(tokens.at(1));
        
    }
    param.numOfVar=std::stoi(lines.at(0));
    param.numRow = std::stoi(lines.at(1));
    param.maxVal=std::stoi(lines.at(2));
    param.minVal=std::stoi(lines.at(3));
    param.seed1 = std::stoi(lines.at(4));
    param.namefiledat1 = lines.at(5);
    param.namefiledat2 = lines.at(6);
    param.bin = std::stoi(lines.at(7));
    param.max_tn = std::stoi(lines.at(8));
    param.min_tn = std::stoi(lines.at(9));
    return param;
}
