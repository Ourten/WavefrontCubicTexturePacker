//
// Created by Ourten on 21/06/2018.
//

#include "wavefront_parser.h"

std::vector<Block> extractBlocks(std::string filePath, int imgWidth, int imgHeight)
{
    std::vector<std::pair<double, double>> uvParts;

    std::ifstream in(filePath);
    for (std::string line(" "); std::getline(in, line);)
    {
        if (line.find("vt ") != std::string::npos)
        {
            std::vector<std::string> parts = split(line, ' ');
            uvParts.emplace_back(stod(parts.at(1)), stod(parts.at(2)));
        }
    }
    in.close();

    std::vector<Block> blocks;
    unsigned int duplicates = 0;

    for (unsigned int i = 0; i < uvParts.size(); i += 4)
    {
        std::pair<double, double> firstPoint = uvParts.at(i);
        std::pair<double, double> secondPoint = uvParts.at(i + 1);
        std::pair<double, double> thirdPoint = uvParts.at(i + 2);
        std::pair<double, double> fourthPoint = uvParts.at(i + 3);

        int startX = static_cast<int>(std::min(std::min(firstPoint.first, secondPoint.first),
                                               std::min(thirdPoint.first, fourthPoint.first)) * imgWidth);
        int endX = static_cast<int>(std::max(std::max(firstPoint.first, secondPoint.first),
                                             std::max(thirdPoint.first, fourthPoint.first)) * imgWidth);
        int startY = static_cast<int>(std::min(std::min(firstPoint.second, secondPoint.second),
                                               std::min(thirdPoint.second, fourthPoint.second)) * imgHeight);
        int endY = static_cast<int>(std::max(std::max(firstPoint.second, secondPoint.second),
                                             std::max(thirdPoint.second, fourthPoint.second)) * imgHeight);

        Block block(startX, imgHeight - endY, endX, imgHeight - startY);

        if (std::find(blocks.begin(), blocks.end(), block) == blocks.end())
            blocks.emplace_back(block);
        else
            duplicates++;
    }

    std::sort(blocks.begin(), blocks.end(), std::greater<>());

    std::cout << "Removed " << duplicates << " duplicates during parsing" << std::endl;
    return blocks;
}