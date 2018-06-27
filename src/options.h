//
// Created by Ourten on 22/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_OPTIONS_H
#define WAVEFRONTTEXTUREPACKER_OPTIONS_H

#include <iostream>
#include <fstream>
#include <string>

class Options
{
private:
    std::string objPath;
    std::string pngPath;
    std::string outputPath;
    int evenLevel;
    bool packSimilar;
public:
    Options(const std::string &objPath, const std::string &pngPath, const std::string &outputPath, int evenLevel,
            bool packSimilar);

    const std::string &getObjPath() const;

    const std::string &getPngPath() const;

    int getEvenLevel() const;

    bool isPackSimilar() const;

    const std::string &getOutputPath() const;

    static Options fromArgs(int argc, char **argv);

    static void printHelp();
};


#endif //WAVEFRONTTEXTUREPACKER_OPTIONS_H
