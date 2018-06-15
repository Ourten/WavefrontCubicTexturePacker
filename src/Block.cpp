//
// Created by Ourten on 14/06/2018.
//

#include "Block.h"

Block::Block(float startX, float startY, float endX, float endY)
{
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
}

float Block::getStartX() const
{
    return startX;
}

float Block::getStartY() const
{
    return startY;
}

float Block::getEndX() const
{
    return endX;
}

float Block::getEndY() const
{
    return endY;
}

void Block::setStartX(float startX)
{
    Block::startX = startX;
}

void Block::setStartY(float startY)
{
    Block::startY = startY;
}

void Block::setEndX(float endX)
{
    Block::endX = endX;
}

void Block::setEndY(float endY)
{
    Block::endY = endY;
}

float Block::getWidth() const
{
    return endX - startX;
}

float Block::getHeight() const
{
    return endY - startY;
}

bool Block::operator<(const Block &rhs) const
{
    return std::max(this->getWidth(), this->getHeight()) < std::max(rhs.getWidth(), rhs.getHeight());
}

bool Block::operator>(const Block &rhs) const
{
    return rhs < *this;
}

bool Block::operator<=(const Block &rhs) const
{
    return !(rhs < *this);
}

bool Block::operator>=(const Block &rhs) const
{
    return !(*this < rhs);
}

std::ostream &operator<<(std::ostream &os, const Block &block)
{
    os << " width: " << block.getWidth() << " height: " << block.getHeight()
       << " startX: " << block.startX << " startY: " << block.startY << " endX: " << block.endX << " endY: "
       << block.endY;
    return os;
}
