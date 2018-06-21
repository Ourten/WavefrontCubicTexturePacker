//
// Created by Ourten on 20/06/2018.
//

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../library/stb_image.h"
#include "../library/stb_image_write.h"

Image::Image(int width, int height, int bpp) : width(width), height(height), bpp(bpp)
{
    Image::fromDisk = false;
}

unsigned char *Image::getContent() const
{
    return content;
}

void Image::setContent(unsigned char *content)
{
    Image::content = content;
}

bool Image::isFromDisk() const
{
    return fromDisk;
}

void Image::setFromDisk(bool fromDisk)
{
    Image::fromDisk = fromDisk;
}

int Image::getWidth() const
{
    return width;
}

void Image::setWidth(int width)
{
    Image::width = width;
}

int Image::getHeight() const
{
    return height;
}

void Image::setHeight(int height)
{
    Image::height = height;
}

int Image::getBpp() const
{
    return bpp;
}

void Image::setBpp(int bpp)
{
    Image::bpp = bpp;
}

Image Image::load(std::string path)
{
    int width, height, bpp;
    unsigned char *content = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    Image image(width, height, bpp);
    image.setContent(content);
    image.setFromDisk(true);
    return image;
}

Image Image::createBlank(int width, int height, int bpp)
{
    Image image(width, height, bpp);

    image.content = new unsigned char[width * bpp * height]{0};

    return image;
}

void Image::write(std::string path)
{
    stbi_write_png(path.c_str(), Image::getWidth(), Image::getHeight(), Image::getBpp(),
                   Image::getContent(), Image::getWidth() * Image::getBpp());
}

Image::~Image()
{
    if (Image::isFromDisk())
        stbi_image_free(Image::getContent());
    else
        delete[] Image::content;
}
