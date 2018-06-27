//
// Created by Ourten on 20/06/2018.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "texture_util.h"

int getTexIdx(int imgWidth, int bpp, int x, int y)
{
    return x * bpp + (imgWidth * bpp * y);
}

void copyTex(Image &srcImg, Image &dstImg, Block src, Block dst)
{
    for (int y = 0; y < src.getHeight(); y++)
    {
        for (int x = 0; x < src.getWidth(); x++)
        {
            for (int i = 0; i < srcImg.getBpp(); i++)
            {
                dstImg.getContent()[
                        getTexIdx(dstImg.getWidth(), srcImg.getBpp(), dst.getStartX() + x, dst.getStartY() + y) + i] =
                        srcImg.getContent()[getTexIdx(srcImg.getWidth(), srcImg.getBpp(), src.getStartX() + x,
                                                      src.getStartY() + y) + i];
            }
        }
    }
}

bool isTexPartEquals(Image &image, Block first, Block second)
{
    for (int y = 0; y < first.getHeight(); y++)
    {
        for (int x = 0; x < first.getWidth(); x++)
        {
            for (int i = 0; i < image.getBpp(); i++)
            {
                if (image.getContent()[(first.getStartX() + x * i) + (image.getWidth() * first.getStartY() + y)] !=
                    image.getContent()[(second.getStartX() + x * i) + (image.getWidth() * second.getStartY() + y)])
                    return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<Block, Block>> deleteSimilarBlocks(Image &inputImg, std::vector<Block> &blocks)
{
    int clones = 0;

    std::vector<std::pair<Block, Block>> duplicates;

    for (Block block : blocks)
    {
        for (Block other : blocks)
        {
            if (block != other && block.getWidth() == other.getWidth() && block.getHeight() == other.getHeight() &&
                isTexPartEquals(inputImg, block, other))
            {
                blocks.erase(std::remove(blocks.begin(), blocks.end(), other));
                duplicates.emplace_back(std::pair(other, block));
                clones++;
            }
        }
    }
    std::cout << "Removed " << clones << " clones" << std::endl;
    return duplicates;
}

int getNextSquared(int from)
{
    if (from && ((!from) & (from - 1)))
        return from;
    return static_cast<int>(std::ceil(std::pow(2, std::ceil(std::log2(from)))));
}

int getNextValidSize(int from, int level)
{
    if (level == 0)
        return from + 1;
    if (level == -1)
        return getNextSquared(from);
    if (from % ((int) std::pow(2, level)) == 0)
        return from;
    return from + ((int) std::pow(2, level)) - (from % ((int) std::pow(2, level)));
}