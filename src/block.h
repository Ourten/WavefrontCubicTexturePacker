//
// Created by Ourten on 14/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_BLOCK_H
#define WAVEFRONTTEXTUREPACKER_BLOCK_H


#include <ostream>

class Block
{
private:
    int startX, startY, endX, endY;
public:
    Block(int startX, int startY, int endX, int endY);

    int getStartX() const;

    int getStartY() const;

    int getEndX() const;

    int getEndY() const;

    void setStartX(int startX);

    void setStartY(int startY);

    void setEndX(int endX);

    void setEndY(int endY);

    int getWidth() const;

    int getHeight() const;

    int getArea() const;

    friend std::ostream &operator<<(std::ostream &os, const Block &block);

    bool operator<(const Block &rhs) const;

    bool operator>(const Block &rhs) const;

    bool operator<=(const Block &rhs) const;

    bool operator>=(const Block &rhs) const;

    bool operator==(const Block &rhs) const;

    bool operator!=(const Block &rhs) const;
};


#endif //WAVEFRONTTEXTUREPACKER_BLOCK_H
