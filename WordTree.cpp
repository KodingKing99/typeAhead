#include "WordTree.hpp"

#include <cctype>
#include <iostream>
#include <queue>
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
WordTree::WordTree() :
    mysize(0), root(new TreeNode("root"))
{
}
void WordTree::toString(std::shared_ptr<TreeNode> node)
{
    for (long unsigned int i = 0; i < 26; i++)
    {
        auto treenode = node->children[i];
        if (treenode == nullptr)
        {
            std::cout << "nullptr at " << i << std::endl;
        }
        else
        {
            std::cout << treenode->nodename << std::endl;
        }
    }
}
void WordTree::add(std::string word)
{
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
        // auto parent = currNode->children[index];
        if (currNode->children[index] == nullptr)
        {
            currNode->children[index] = std::shared_ptr<TreeNode>(new TreeNode());
            currNode->children[index]->nodename = word[i];
        }
        currNode = currNode->children[index];
        if (i == word.size() - 1 && !currNode->endOfWord)
        {
            currNode->endOfWord = true;
            mysize++;
        }
    }
}
bool WordTree::find(std::string word)
{
    if (word.size() == 0)
    {
        return false;
    }
    return findRecursive(word, root, 0);
}

bool WordTree::findRecursive(std::string word, std::shared_ptr<TreeNode> currNode, long unsigned int i)
{
    if (i >= word.size() && currNode->endOfWord)
    {
        return true;
    }
    if (i >= word.size())
    {
        return false;
    }

    auto index = getMyIndex(word, i);
    currNode = currNode->children[index];
    if (currNode == nullptr)
    {
        std::cout << "NullPtr!!" << std::endl;
        return false;
    }
    i += 1;
    return findRecursive(word, currNode, i);
}
/////////
// Helper function for predict, gets the node corresponding to the partial word
// returns root if not found
/////////
std::shared_ptr<TreeNode> WordTree::getMyNode(std::string partial, std::shared_ptr<TreeNode> currNode, long unsigned int i)
{
    if (i == partial.size())
    {
        return currNode;
    }
    auto index = getMyIndex(partial, i);
    currNode = currNode->children[index];
    if (currNode == nullptr)
    {
        return nullptr;
    }
    i += 1;
    return getMyNode(partial, currNode, i);
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::vector<std::string> outputVec;
    std::queue<std::pair<std::shared_ptr<TreeNode>, std::string>> q;
    if (partial.size() == 0)
    {
        return outputVec;
    }
    auto node = getMyNode(partial, root, 0);
    if (node == nullptr)
    {
        return outputVec;
    }
    q.push(std::make_pair(node, partial));
    while (!q.empty())
    {
        if (outputVec.size() >= howMany)
        {
            break;
        }
        std::pair<std::shared_ptr<TreeNode>, std::string> v = q.front();
        q.pop();
        for (auto node : v.first->children)
        {

            if (node == nullptr)
            {
                continue;
            }
            else
            {
                if (node->endOfWord)
                {
                    outputVec.push_back(v.second + node->nodename);
                }
                q.push(std::make_pair(node, v.second + node->nodename));
            }
        }
    }
    return outputVec;
}
std::size_t WordTree::size()
{
    return mysize;
}
