#include "WordTree.hpp"

#include <iostream>
int main()
{
    std::cout << "Hello World" << std::endl;
    WordTree tree;
    tree.add("hello");
    std::cout << "Tree size after adding: " << tree.size() << std::endl;
    for (long unsigned int i = 0; i < 26; i++)
    {
        auto treenode = tree.root->children[i];
        if (treenode == nullptr)
        {
            std::cout << "nullptr at " << i << std::endl;
        }
        else
        {
            std::cout << treenode->endOfWord << std::endl;
        }
        // std::cout << treenode->endOfWord << std::endl;
    }
    // auto wordFound = tree.find("hello");
    // std::cout << "Found hello? " << wordFound << std::endl;
    return 0;
}
