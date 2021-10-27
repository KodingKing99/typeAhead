#include "WordTree.hpp"

#include <cctype>
#include <iostream>
TreeNode::TreeNode() :
    endOfWord(false) {}
WordTree::WordTree() :
    mysize(0), root(new TreeNode()) {}
void WordTree::add(std::string word)
{
    std::cout << "adding the word " << word << std::endl;

    for (auto i : word)
    {
        std::cout << i << std::endl;
        int index = static_cast<int>(i);
        std::cout << "char value: " << index << std::endl;
    }
    mysize++;
}