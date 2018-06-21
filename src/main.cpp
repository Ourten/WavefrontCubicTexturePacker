#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "block.h"
#include "node.h"
#include "image.h"
#include "texture_util.h"
#include "block_packer.h"
#include "wavefront_parser.h"

int main(int argc, char *argv[])
{
    std::string pngPath, objPath;

    for (int i = 1; i < argc; i++)
    {
        if ("-png" == std::string(argv[i]) && i + 1 != argc)
        {
            pngPath = argv[i + 1];
            i++;
        }
        else if ("-obj" == std::string(argv[i]) && i + 1 != argc)
        {
            objPath = argv[i + 1];
            i++;
        }
        else if (i + 1 == argc && argv[i][0] != '-')
        {
            pngPath = argv[i];
            pngPath += ".png";

            objPath = argv[i];
            objPath += ".obj";
        }
    }
    std::cout << pngPath << " " << objPath << std::endl;

    Image inputImg = Image::load(pngPath);

    std::cout << "Width: " << inputImg.getWidth() << " Height: " << inputImg.getHeight() << std::endl;

    std::vector<Block> blocks = extractBlocks(objPath, inputImg.getWidth(), inputImg.getHeight());

    int totalArea = 0;
    for (Block block : blocks)
    {
        totalArea += block.getArea();
        std::cout << block << std::endl;
    }

    deleteSimilarBlocks(inputImg, blocks);

    std::cout << blocks.size() << " elements left" << std::endl;
    std::cout << "Area: " << totalArea << std::endl;

    int evenLevel = 4;

    int minimalSize = getNextValidSize((int) (std::ceil(std::sqrt(totalArea))), evenLevel);

    std::cout << "Original Size: " << inputImg.getWidth() << "x" << inputImg.getHeight() << std::endl;
    std::cout << "Minimal Size: " << minimalSize << "x" << minimalSize << std::endl;

    Node root(0, 0, minimalSize, minimalSize);

    Image outputImg = Image::createBlank(root.getWidth(), root.getHeight(), inputImg.getBpp());

    std::vector<std::pair<Block, Block>> sortedBlocks = fit(blocks, root, evenLevel);
    std::cout << "Computed Size: " << root.getWidth() << "x" << root.getHeight() << std::endl;

    for (std::pair<Block, Block> transformed :  sortedBlocks)
    {
        std::cout << transformed.second << std::endl;
        copyTex(inputImg, outputImg, transformed.first, transformed.second);
    }

    outputImg.write("output.png");
    return 0;
}
