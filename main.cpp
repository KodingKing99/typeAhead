#include "WordTree.hpp"

#include <iostream>
int main()
{
    std::cout << "Hello World" << std::endl;
    WordTree tree;
    tree.add("heLLo");
    std::cout << "Tree size after adding: " << tree.size() << std::endl;
    return 0;
}
