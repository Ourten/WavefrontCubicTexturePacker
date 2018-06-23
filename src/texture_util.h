//
// Created by Ourten on 21/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_TEXTURE_UTIL_H
#define WAVEFRONTTEXTUREPACKER_TEXTURE_UTIL_H

#include "image.h"
#include "block.h"

bool isTexPartEquals(Image &image, Block first, Block second);

void copyTex(Image &srcImg, Image &dstImg, Block src, Block dst);

std::vector<std::pair<Block, Block>> deleteSimilarBlocks(Image &inputImg, std::vector<Block> &blocks);

int getNextValidSize(int from, int level);

#endif //WAVEFRONTTEXTUREPACKER_TEXTURE_UTIL_H
