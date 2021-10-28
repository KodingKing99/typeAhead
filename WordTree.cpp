#include "WordTree.hpp"

#include <cctype>
#include <iostream>
// #include <functional>
const int ALPHAVAL = 97;
int getMyIndex(std::string word, int ind)
{
    int index = static_cast<int>(std::tolower(word[ind]));
    index -= ALPHAVAL;
    return index;
}
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
        // if the char is not an alphabetical
        if (std::isalpha(word[i]) == 0)
        {
            std::cout << "Not alphabetic..." << std::endl;
            continue;
        }
        // hello[0] = h = 7
        int index = getMyIndex(word, i);
        // If the value is not already there
        std::cout << "currnode before: " << currNode << std::endl;
        auto child = currNode->children[index];
        if (child == nullptr)
        {
            child = std::shared_ptr<TreeNode>(new TreeNode());
            std::cout << "child: " << child << std::endl;
        }
        currNode = child;
        std::cout << "currnode after: " << currNode << "\n"
                  << std::endl;
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
bool WordTree::find(std::string word)
{
    return findRecursive(word, root, 0);
}

bool WordTree::findRecursive(std::string word, std::shared_ptr<TreeNode> currNode, int i)
{
    auto index = getMyIndex(word, i);
    std::cout << "my index: " << index << std::endl;
    std::cout << currNode->children[index] << std::endl;
    currNode = currNode->children[index];

    if (currNode == nullptr)
    {
        std::cout << "NullPtr!!" << std::endl;
        return false;
    }
    if (currNode->endOfWord == true)
    {
        std::cout << "Found word" << std::endl;
        return true;
    }
    return findRecursive(word, currNode, i++);
}
std::size_t WordTree::size()
{
    return mysize;
}
