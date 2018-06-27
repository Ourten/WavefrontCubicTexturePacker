//
// Created by Ourten on 14/06/2018.
//

#include "../include/block.h"

Block::Block(int startX, int startY, int endX, int endY)
{
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
}

int Block::getStartX() const
{
    return startX;
}

int Block::getStartY() const
{
    return startY;
}

int Block::getEndX() const
{
    return endX;
}

int Block::getEndY() const
{
    return endY;
}

void Block::setStartX(int startX)
{
    Block::startX = startX;
}

void Block::setStartY(int startY)
{
    Block::startY = startY;
}

void Block::setEndX(int endX)
{
    Block::endX = endX;
}

void Block::setEndY(int endY)
{
    Block::endY = endY;
}

int Block::getWidth() const
{
    return endX - startX;
}

int Block::getHeight() const
{
    return endY - startY;
}

int Block::getArea() const
{
    return getWidth() * getHeight();
}

bool Block::operator==(const Block &rhs) const
{
    return this->startX == rhs.startX &&
           this->startY == rhs.startY &&
           this->endX == rhs.endX &&
           this->endY == rhs.endY;
}

bool Block::operator!=(const Block &rhs) const
{
    return !(rhs == *this);
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
