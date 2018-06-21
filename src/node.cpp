//
// Created by Ourten on 18/06/2018.
//

#include "node.h"


Node::Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{
    used = false;
}

int Node::getX() const
{
    return x;
}

void Node::setX(int x)
{
    Node::x = x;
}

int Node::getY() const
{
    return y;
}

void Node::setY(int y)
{
    Node::y = y;
}

int Node::getWidth() const
{
    return width;
}

void Node::setWidth(int width)
{
    Node::width = width;
}

int Node::getHeight() const
{
    return height;
}

void Node::setHeight(int height)
{
    Node::height = height;
}

bool Node::isUsed() const
{
    return used;
}

void Node::setUsed(bool used)
{
    Node::used = used;
}
