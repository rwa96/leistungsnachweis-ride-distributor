#include <iostream>
#include <fstream>

#include "input_data.h"

InputData::InputData(const std::string path){
    std::ifstream file(path);
    std::string line;

    if(!file){
        //TODO Error
    }

    if(std::getline(file, line)){
        std::istringstream iss(line);
        iss >> r >> c >> f >> n >> b >> t;
    }
}
