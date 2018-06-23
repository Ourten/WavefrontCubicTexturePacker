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
#include "Options.h"

int main(int argc, char *argv[])
{
    Options options = Options::fromArgs(argc, argv);

    Image inputImg = Image::load(options.getPngPath());

    std::cout << "Width: " << inputImg.getWidth() << " Height: " << inputImg.getHeight() << std::endl;

    std::vector<Block> blocks = extractBlocks(options.getObjPath(), inputImg.getWidth(), inputImg.getHeight());

    int totalArea = 0;
    for (Block block : blocks)
    {
        totalArea += block.getArea();
        std::cout << block << std::endl;
    }

    std::vector<std::pair<Block, Block>> similarBlocks;

    if (options.isPackSimilar())
        similarBlocks = deleteSimilarBlocks(inputImg, blocks);

    std::cout << blocks.size() << " elements left" << std::endl;
    std::cout << "Area: " << totalArea << std::endl;

    int minimalSize = getNextValidSize((int) (std::ceil(std::sqrt(totalArea))), options.getEvenLevel());

    std::cout << "Original Size: " << inputImg.getWidth() << "x" << inputImg.getHeight() << std::endl;
    std::cout << "Minimal Size: " << minimalSize << "x" << minimalSize << std::endl;

    Node root(0, 0, minimalSize, minimalSize);

    Image outputImg = Image::createBlank(root.getWidth(), root.getHeight(), inputImg.getBpp());

    std::vector<std::pair<Block, Block>> sortedBlocks = fit(blocks, root, options.getEvenLevel());
    std::cout << "Computed Size: " << root.getWidth() << "x" << root.getHeight() << std::endl;

    for (std::pair<Block, Block> transformed :  sortedBlocks)
    {
        std::cout << transformed.second << std::endl;
        copyTex(inputImg, outputImg, transformed.first, transformed.second);
    }

    outputImg.write(options.getOutputPath() + ".png");
    return 0;
}
