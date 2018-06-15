#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION

std::vector<std::string> split(const std::string &basic_string, char i);

#include "../library/stb_image.h"
#include "Block.h"

int main()
{
    int width, height, bpp;
    unsigned char *rgb = stbi_load("resources/belt.png", &width, &height, &bpp, 3);

    std::cout << "Width: " << width << " Height: " << height << std::endl;

    std::vector<std::pair<float, float>> uvParts;

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

    std::list<Block> blocks;

    for (unsigned int i = 0; i < uvParts.size(); i += 4)
    {
        std::pair<float, float> firstPoint = uvParts.at(i);
        std::pair<float, float> secondPoint = uvParts.at(i + 1);
        std::pair<float, float> thirdPoint = uvParts.at(i + 2);
        std::pair<float, float> fourthPoint = uvParts.at(i + 3);

        float startX = std::min(std::min(firstPoint.first, secondPoint.first),
                                std::min(thirdPoint.first, fourthPoint.first)) * width;
        float endX = std::max(std::max(firstPoint.first, secondPoint.first),
                              std::max(thirdPoint.first, fourthPoint.first)) * width;
        float startY = std::min(std::min(firstPoint.second, secondPoint.second),
                                std::min(thirdPoint.second, fourthPoint.second)) * height;
        float endY = std::max(std::max(firstPoint.second, secondPoint.second),
                              std::max(thirdPoint.second, fourthPoint.second)) * height;

        blocks.emplace_back(Block(startX, startY, endX, endY));
    }

    blocks.sort();
    for (Block block : blocks)
    {
        std::cout << block << std::endl;
    }

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