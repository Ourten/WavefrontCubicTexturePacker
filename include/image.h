//
// Created by Ourten on 20/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_IMAGE_H
#define WAVEFRONTTEXTUREPACKER_IMAGE_H

#include <string>
#include <memory>

class Image
{
private:
    unsigned char* content;
    bool fromDisk;

    int width, height, bpp;
public:
    Image(int width, int height, int bpp);

    static Image load(std::string path);

    static Image createBlank(int width, int height, int bpp);

    void write(std::string path);

    unsigned char *getContent() const;

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getBpp() const;

    void setBpp(int bpp);

    void setContent(unsigned char *content);

    bool isFromDisk() const;

    void setFromDisk(bool fromDisk);

    virtual ~Image();
};

#endif //WAVEFRONTTEXTUREPACKER_IMAGE_H
