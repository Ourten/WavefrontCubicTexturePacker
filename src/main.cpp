#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION

std::vector<std::string> split(const std::string &basic_string, char i);

#include "../library/stb_image.h"

int main()
{
    int width, height, bpp;
    unsigned char *rgb = stbi_load("resources/belt.png", &width, &height, &bpp, 3);

    std::cout << "Width: " << width << " Height: " << height << std::endl;

    std::list<std::pair<float, float>> uvParts;

    std::ifstream in("resources/belt.obj");

    for (std::string line(" "); getline(in, line);)
    {
        if (line.find("vt ") != std::string::npos)
        {
            std::cout << line << std::endl;
            std::vector<std::string> parts = split(line, ' ');
            uvParts.emplace_back(stof(parts.at(1)), stof(parts.at(2)));
        }
    }
    in.close();

    return 0;
}

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