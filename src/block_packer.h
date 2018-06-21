//
// Created by Ourten on 21/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_BLOCK_PACKER_H
#define WAVEFRONTTEXTUREPACKER_BLOCK_PACKER_H

#include <iostream>
#include <vector>

#include "block.h"
#include "node.h"
#include "texture_util.h"

std::vector<std::pair<Block, Block>> fit(std::vector<Block> blocks, Node &root, int level);

#endif //WAVEFRONTTEXTUREPACKER_BLOCK_PACKER_H
