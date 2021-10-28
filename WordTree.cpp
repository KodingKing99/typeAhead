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
    auto currNode = root;
    for (long unsigned int i = 0; i < word.size(); i++)
    {
        // std::cout << word[i] << std::endl;
        // if the char is not an alphabetical
        if (std::isalpha(word[i]) == 0)
        {
            std::cout << "Not alphabetic..." << std::endl;
            continue;
        }
        int index = static_cast<int>(std::tolower(word[i]));
        // convert to 0 - 25 for array
        index -= 97;
        // std::cout << "char value: " << index << std::endl;
        // std::cout << "Tree node at index: " << root->children[index] << std::endl;
        // If the value is not already there
        auto node = currNode->children[index];
        if (node == nullptr)
        {
            std::cout << "Null ptr!" << std::endl;
            node = std::shared_ptr<TreeNode>(new TreeNode());
        }
        if (node == nullptr)
        {
            std::cout << "Still a null ptr!" << std::endl;
        }
        currNode = node;
        // if you are at the end of the word
        if (i == word.size() - 1)
        {
            currNode->endOfWord = true;
        }
        std::cout << "Current node end of word? " << currNode->endOfWord << std::endl;
    }
    if (currNode->endOfWord == true)
    {
        mysize++;
    }
}
std::size_t WordTree::size()
{
    return mysize;
}
