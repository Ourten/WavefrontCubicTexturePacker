//
// Created by Ourten on 21/06/2018.
//

#include "../include/wavefront_parser.h"

std::pair<double, double> getPointFromLine(const std::string &line)
{
    std::vector<std::string> parts = split(line, ' ');
    return std::pair(stod(parts.at(1)), stod(parts.at(2)));
}

Block
getBlockFromLines(std::string &firstLine, std::string &secondLine, std::string &thirdLine, std::string &fourthLine,
                  int imgWidth, int imgHeight)
{
    std::pair<double, double> firstPoint = getPointFromLine(firstLine);
    std::pair<double, double> secondPoint = getPointFromLine(secondLine);
    std::pair<double, double> thirdPoint = getPointFromLine(thirdLine);
    std::pair<double, double> fourthPoint = getPointFromLine(fourthLine);

    auto startX = static_cast<int>(std::min(std::min(firstPoint.first, secondPoint.first),
                                            std::min(thirdPoint.first, fourthPoint.first)) * imgWidth);
    auto endX = static_cast<int>(std::max(std::max(firstPoint.first, secondPoint.first),
                                          std::max(thirdPoint.first, fourthPoint.first)) * imgWidth);
    auto startY = static_cast<int>(std::min(std::min(firstPoint.second, secondPoint.second),
                                            std::min(thirdPoint.second, fourthPoint.second)) * imgHeight);
    auto endY = static_cast<int>(std::max(std::max(firstPoint.second, secondPoint.second),
                                          std::max(thirdPoint.second, fourthPoint.second)) * imgHeight);

    return Block(startX, imgHeight - endY, endX, imgHeight - startY);
}

void replacePointValues(std::pair<double, double> &point, double x, double y, double startX, double endX, double startY,
                        double endY)
{
    if (point.first == x)
        point.first = startX;
    else
        point.first = endX;

    // Invert check because of flip-v
    if (point.second != y)
        point.second = startY;
    else
        point.second = endY;
}

void replaceBlockLines(Block newBlock, std::string &firstLine, std::string &secondLine, std::string &thirdLine,
                       std::string &fourthLine, int imgWidth, int imgHeight)
{
    std::pair<double, double> firstPoint = getPointFromLine(firstLine);
    std::pair<double, double> secondPoint = getPointFromLine(secondLine);
    std::pair<double, double> thirdPoint = getPointFromLine(thirdLine);
    std::pair<double, double> fourthPoint = getPointFromLine(fourthLine);

    double startX = std::min(std::min(firstPoint.first, secondPoint.first),
                             std::min(thirdPoint.first, fourthPoint.first));
    double startY = std::min(std::min(firstPoint.second, secondPoint.second),
                             std::min(thirdPoint.second, fourthPoint.second));

    replacePointValues(firstPoint, startX, startY, static_cast<double>(newBlock.getStartX()) / imgWidth,
                       static_cast<double>(newBlock.getEndX()) / imgWidth,
                       static_cast<double>(imgHeight - newBlock.getStartY()) / imgHeight,
                       static_cast<double>(imgHeight - newBlock.getEndY()) / imgHeight);

    replacePointValues(secondPoint, startX, startY, static_cast<double>(newBlock.getStartX()) / imgWidth,
                       static_cast<double>(newBlock.getEndX()) / imgWidth,
                       static_cast<double>(imgHeight - newBlock.getStartY()) / imgHeight,
                       static_cast<double>(imgHeight - newBlock.getEndY()) / imgHeight);

    replacePointValues(thirdPoint, startX, startY, static_cast<double>(newBlock.getStartX()) / imgWidth,
                       static_cast<double>(newBlock.getEndX()) / imgWidth,
                       static_cast<double>(imgHeight - newBlock.getStartY()) / imgHeight,
                       static_cast<double>(imgHeight - newBlock.getEndY()) / imgHeight);

    replacePointValues(fourthPoint, startX, startY, static_cast<double>(newBlock.getStartX()) / imgWidth,
                       static_cast<double>(newBlock.getEndX()) / imgWidth,
                       static_cast<double>(imgHeight - newBlock.getStartY()) / imgHeight,
                       static_cast<double>(imgHeight - newBlock.getEndY()) / imgHeight);

    firstLine = "vt " + std::to_string(firstPoint.first) + " " + std::to_string(firstPoint.second);
    secondLine = "vt " + std::to_string(secondPoint.first) + " " + std::to_string(secondPoint.second);
    thirdLine = "vt " + std::to_string(thirdPoint.first) + " " + std::to_string(thirdPoint.second);
    fourthLine = "vt " + std::to_string(fourthPoint.first) + " " + std::to_string(fourthPoint.second);
}

void writeBlocks(std::string filePath, std::string originalFile, int inputWidth, int inputHeight, int outputWidth,
                 int outputHeight, std::vector<std::pair<Block, Block>> transformed,
                 std::vector<std::pair<Block, Block>> duplicates)
{
    std::ifstream in(originalFile);
    std::ofstream out(filePath);

    for (std::string line(" "); std::getline(in, line);)
    {
        if (line.find("vt ") == std::string::npos)
        {
            out << line << std::endl;
            continue;
        }

        std::string secondLine(" ");
        std::string thirdLine(" ");
        std::string fourthLine(" ");

        std::getline(in, secondLine);
        std::getline(in, thirdLine);
        std::getline(in, fourthLine);

        Block extracted = getBlockFromLines(line, secondLine, thirdLine, fourthLine, inputWidth, inputHeight);

        if (!duplicates.empty())
        {
            for (std::pair<Block, Block> pair : duplicates)
            {
                if (pair.first == extracted)
                    extracted = pair.second;
            }
        }
        for (std::pair<Block, Block> pair : transformed)
        {
            if (pair.first == extracted)
            {
                replaceBlockLines(pair.second, line, secondLine, thirdLine, fourthLine, outputWidth, outputHeight);
                out << line << std::endl;
                out << secondLine << std::endl;
                out << thirdLine << std::endl;
                out << fourthLine << std::endl;
            }
        }
    }
}

std::vector<Block> extractBlocks(std::string filePath, int imgWidth, int imgHeight)
{
    std::vector<Block> blocks;
    unsigned int duplicates = 0;

    std::ifstream in(filePath);
    for (std::string line(" "); std::getline(in, line);)
    {
        if (line.find("vt ") != std::string::npos)
        {
            std::string secondLine(" ");
            std::string thirdLine(" ");
            std::string fourthLine(" ");

            std::getline(in, secondLine);
            std::getline(in, thirdLine);
            std::getline(in, fourthLine);

            Block block = getBlockFromLines(line, secondLine, thirdLine, fourthLine, imgWidth, imgHeight);
            if (std::find(blocks.begin(), blocks.end(), block) == blocks.end())
                blocks.emplace_back(block);
            else
                duplicates++;
        }
    }
    std::sort(blocks.begin(), blocks.end(), std::greater<>());

    std::cout << "Removed " << duplicates << " duplicates during parsing" << std::endl;
    return blocks;
}