//
// Created by Ourten on 22/06/2018.
//

#include "../include/options.h"

Options::Options(const std::string &objPath, const std::string &pngPath, const std::string &outputPath, int evenLevel,
                 bool packSimilar) : objPath(objPath), pngPath(pngPath), outputPath(outputPath), evenLevel(evenLevel),
                                     packSimilar(packSimilar)
{}

Options Options::fromArgs(int argc, char *argv[])
{
    std::string pngPath, objPath;

    std::string outputPath = "output";
    int evenLevel = 0;
    bool packSimilar = false;

    for (int i = 1; i < argc; i++)
    {
        if ("-h" == std::string(argv[i]) || "--help" == std::string(argv[i]))
        {
            Options::printHelp();
            std::exit(0);
        }
        else if ("--png" == std::string(argv[i]) && i + 1 != argc)
        {
            pngPath = argv[i + 1];
            i++;
        }
        else if ("--obj" == std::string(argv[i]) && i + 1 != argc)
        {
            objPath = argv[i + 1];
            i++;
        }
        else if (("-o" == std::string(argv[i]) || "--output" == std::string(argv[i])) && i + 1 != argc)
        {
            outputPath = argv[i + 1];
            i++;
        }
        else if (("-e" == std::string(argv[i]) || "--even-level" == std::string(argv[i])) && i + 1 != argc)
        {
            evenLevel = std::stoi(argv[i + 1]);
            i++;
        }
        else if ("-p" == std::string(argv[i]) || "--pack-similar" == std::string(argv[i]))
        {
            packSimilar = true;
        }
        else if (i + 1 == argc && argv[i][0] != '-')
        {
            pngPath = argv[i];
            pngPath += ".png";

            objPath = argv[i];
            objPath += ".obj";
        }
    }

    if (!std::ifstream(objPath))
    {
        std::cerr << "OBJ file <" << objPath << "> does not exist!";
        std::exit(EXIT_FAILURE);
    }
    if (!std::ifstream(pngPath))
    {
        std::cerr << "PNG file <" << objPath << "> does not exist!";
        std::exit(EXIT_FAILURE);
    }
    return Options(objPath, pngPath, outputPath, evenLevel, packSimilar);
}

void Options::printHelp()
{
    std::cout << "usage: wavefronttexturepacker [options] [<FILE NAME>]\n"
                 "  The specified FILE NAME must be without extension and match the name of both png and obj files.\n"
                 "  For differing names the --png and --obj options can be used.\n\n"
                 "  options:\n"
                 "    --png <FILE>               specify the file path of the png file used for input\n"
                 "    --obj <FILE>               specify the file path of the obj file used for input\n"
                 "    -o, --output <FILE NAME>   specify the file path without the extension to use for output of both png and obj files\n\n"
                 "    -e, --even-level <NUMBER>  how many times the size of the output texture remains even when divided by two;\n"
                 "                               for example -e 1 will allow any size divisible by 2, -e 2 divisible by 4 and so on.\n"
                 "                               Using -e -1 will make the output size a power of two like 16, 32, 64...\n"
                 "                               Using -e 0 is the same as not specifying the even level, any size is allowed.\n\n"
                 "    -p, --pack-similar         if specified this flag will allow removal of duplicated texture parts;\n"
                 "                               any faces of the same size with identical pixels values will be considered equals.\n"
                 "    -h, --help                 show this help message."
              << std::endl;
}

const std::string &Options::getObjPath() const
{
    return objPath;
}

const std::string &Options::getPngPath() const
{
    return pngPath;
}

int Options::getEvenLevel() const
{
    return evenLevel;
}

bool Options::isPackSimilar() const
{
    return packSimilar;
}

const std::string &Options::getOutputPath() const
{
    return outputPath;
}
