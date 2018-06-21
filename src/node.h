//
// Created by Ourten on 18/06/2018.
//

#ifndef WAVEFRONTTEXTUREPACKER_NODE_H
#define WAVEFRONTTEXTUREPACKER_NODE_H

#include <optional>
#include <memory>

class Node
{
private:
    int x, y, width, height;
    bool used;
public:
    std::unique_ptr<Node> down, right;

    Node(int x, int y, int width, int height);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    bool isUsed() const;

    void setUsed(bool used);
};


#endif //WAVEFRONTTEXTUREPACKER_NODE_H
