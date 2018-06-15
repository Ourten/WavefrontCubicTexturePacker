//
// Created by Ourten on 14/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_BLOCK_H
#define WAVEFRONTTEXTUREPACKER_BLOCK_H


#include <ostream>

class Block
{
private:
    float startX, startY, endX, endY;
public:
    Block(float startX, float startY, float endX, float endY);

    float getStartX() const;

    float getStartY() const;

    float getEndX() const;

    float getEndY() const;

    void setStartX(float startX);

    void setStartY(float startY);

    void setEndX(float endX);

    void setEndY(float endY);

    float getWidth() const;

    float getHeight() const;

    friend std::ostream &operator<<(std::ostream &os, const Block &block);

    bool operator<(const Block &rhs) const;

    bool operator>(const Block &rhs) const;

    bool operator<=(const Block &rhs) const;

    bool operator>=(const Block &rhs) const;
};


#endif //WAVEFRONTTEXTUREPACKER_BLOCK_H
