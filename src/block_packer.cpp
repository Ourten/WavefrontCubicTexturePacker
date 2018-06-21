//
// Created by Ourten on 21/06/2018.
//

#include "block_packer.h"

Node *findNode(Node *root, int width, int height)
{
    if (root->isUsed())
    {
        Node *node = findNode(root->right.get(), width, height);

        if (node)
            return node;
        else
            return findNode(root->down.get(), width, height);
    }
    if (width <= root->getWidth() && height <= root->getHeight())
        return root;
    return nullptr;
}

Node *splitNode(Node *node, int width, int height)
{
    node->setUsed(true);

    node->down = std::make_unique<Node>(
            Node(node->getX(), node->getY() + height, node->getWidth(), node->getHeight() - height));
    node->right = std::make_unique<Node>(Node(node->getX() + width, node->getY(), node->getWidth() - width, height));
    return node;
}

std::vector<std::pair<Block, Block>> fit(std::vector<Block> blocks, Node &root, int level)
{
    std::vector<std::pair<Block, Block>> sorted;

    for (int i = 0; i < blocks.size(); i++)
    {
        Block block = blocks[i];
        int width = block.getWidth();
        int height = block.getHeight();

        Node *node = findNode(&root, width, height);
        if (node)
        {
            Node *fit = splitNode(node, width, height);
            sorted.emplace_back(
                    std::pair(block, Block(fit->getX(), fit->getY(), fit->getX() + width, fit->getY() + height)));
        }
        else
        {
            int newSize = getNextValidSize(root.getWidth() + 1, level);

            root = Node(0, 0, newSize, newSize);
            return fit(blocks, root, level);
        }
    }
    return sorted;
}