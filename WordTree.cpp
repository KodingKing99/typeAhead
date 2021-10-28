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
    endOfWord(false), nodename("no name") {}
TreeNode::TreeNode(std::string name) :
    endOfWord(false), nodename(name) {}
// TreeNode::setnodename(std::st)
WordTree::WordTree() :
    mysize(0), root(new TreeNode("root"))
{
}
void WordTree::toString()
{
    for (long unsigned int i = 0; i < 26; i++)
    {
        auto treenode = root->children[i];
        if (treenode == nullptr)
        {
            std::cout << "nullptr at " << i << std::endl;
        }
        else
        {
            std::cout << treenode->nodename << std::endl;
        }
        // std::cout << treenode->endOfWord << std::endl;
    }
}
void WordTree::add(std::string word)
{
    std::cout << "adding the word at index: " << getMyIndex(word, 0) << " " + word << std::endl;
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
        std::cout << "currnode before: " << currNode << " " + currNode->nodename << std::endl;
        // auto child = currNode->children[index];
        if (currNode->children[index] == nullptr)
        {
            currNode->children[index] = std::shared_ptr<TreeNode>(new TreeNode());
            std::cout << "child: " << currNode->children[index] << " " + currNode->children[index]->nodename << std::endl;
            currNode->children[index]->nodename = word[i];
            std::cout << "child: " << currNode->children[index] << " " + currNode->children[index]->nodename << std::endl;
            // toString();
            // std::cout << "\nRoot at h: " << root->children[7] << std::endl;
        }
        // toString();
        std::cout << "\nRoot at h: " << root->children[7] << std::endl;
        // currNode = std::shared_ptr<TreeNode>(*(currNode->children[index]));
        currNode = currNode->children[index];
        std::cout << "currnode after: " << currNode << " " + currNode->nodename + "\n"
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
    toString();
    std::cout << "root at 7: " << root->children[7]->nodename << " next node: " << root->children[7]->children[4]->nodename << " next node: " << root->children[7]->children[4]->children[11]->nodename << std::endl;
}
bool WordTree::find(std::string word)
{
    std::cout << "In find: " + root->nodename << root << std::endl;
    toString();

    return findRecursive(word, root, 0);
}

bool WordTree::findRecursive(std::string word, std::shared_ptr<TreeNode> currNode, int i)
{
    std::cout << "i: " << i << std::endl;
    auto index = getMyIndex(word, i);
    std::cout << "my index: " << index << std::endl;
    std::cout << currNode->children[index] << " " + currNode->nodename << std::endl;
    currNode = currNode->children[index];
    // std::cout << currNode <<
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
    i += 1;
    return findRecursive(word, currNode, i);
}
std::size_t WordTree::size()
{
    return mysize;
}
