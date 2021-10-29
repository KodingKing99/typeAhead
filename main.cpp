#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
void doPredict()
{
    int count = 0;
    rlutil::cls();
    while (count < 10)
    {
        auto keypress = rlutil::getkey();
        std::cout << keypress << static_cast<char>(keypress) << std::endl;

        count++;
    }
}
std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        std::cout << "hi" << std::endl;
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}
int main()
{
    std::cout << "Hello World" << std::endl;
    WordTree tree;
    tree.add("hello");
    std::cout << "Tree size after adding: " << tree.size() << std::endl;
    // std::cout << "added node at index "
    std::cout << tree.root << tree.root->nodename << std::endl;
    tree.add("help");
    // for (long unsigned int i = 0; i < 26; i++)
    // {
    //     auto treenode = tree.root->children[i];
    //     if (treenode == nullptr)
    //     {
    //         std::cout << "nullptr at " << i << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << treenode->endOfWord << std::endl;
    //     }
    //     // std::cout << treenode->endOfWord << std::endl;
    // }
    auto wordFound = tree.find("hello");
    std::cout << "Found hello? " << wordFound << std::endl;
    auto outputVec = tree.predict("hel", 1);
    std::cout << "reading from dict..." << std::endl;
    readDictionary("../dictionary.txt");
    doPredict();
    // std::cout << "Output vec after predict: " << std::endl;
    // for (auto i : outputVec)
    // {
    //     std::cout << i << std::endl;
    // }

    return 0;
}
