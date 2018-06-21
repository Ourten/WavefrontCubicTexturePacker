//
// Created by Ourten on 21/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_WAVEFRONT_PARSER_H
#define WAVEFRONTTEXTUREPACKER_WAVEFRONT_PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "block.h"
#include "string_util.h"

std::vector<Block> extractBlocks(std::string filePath, int imgWidth, int imgHeight);

#endif //WAVEFRONTTEXTUREPACKER_WAVEFRONT_PARSER_H
