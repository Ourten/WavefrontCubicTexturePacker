//
// Created by Ourten on 21/06/2018.
//

#include <string>
#include <vector>
#include <sstream>
#include "string_util.h"

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token(" ");
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}