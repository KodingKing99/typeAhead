#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
template <typename Out>
void split(const std::string& s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
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
void showPredictions(std::pair<int, int> cursor, std::shared_ptr<WordTree> tree, std::string partial)
{
    // go to next line
    // auto HOWMANY = rlutil::trows() - 1;
    auto HOWMANY = 3;
    // std::cout << "Number of rows: " << HOWMANY << std::endl;
    rlutil::locate(1, 2);
    for (std::size_t i = 0; i < 20; i++)
    {
        std::cout << std::string(40, ' ') << std::endl;
    }
    rlutil::locate(1, 2); // put it back
    if (partial.size() > 0)
    {
        for (auto word : tree->predict(*split(partial, ' ').rbegin(), HOWMANY))
        {
            std::cout << word << std::endl;
        }
    }
    rlutil::locate(cursor.first, cursor.second);
}
void debug(std::string partial, std::pair<int, int> cursor)
{
    // move cursor down to debug area
    rlutil::locate(1, 15);
    // print stuff
    std::cout << "partial: " << partial << std::endl;
    std::cout << "cursor: " << std::get<0>(cursor) << ", " << std::get<1>(cursor) << std::endl;
    // move it back
    rlutil::locate(std::get<0>(cursor), std::get<1>(cursor));
}
void doPredict()
{
    int ENTERKEY = 10;
    int count = 0;
    auto tree = readDictionary("../dictionary.txt");
    rlutil::cls();
    auto cursor = std::make_pair(1, 1);
    std::string partial = "";
    while (true)
    {
        auto keypress = rlutil::getkey();
        if (keypress == rlutil::KEY_BACKSPACE)
        {
            cursor.first -= 1;
            rlutil::locate(cursor.first, cursor.second);
            rlutil::setChar(' ');
            partial = partial.substr(0, partial.length() - 1);
        }
        else if (keypress == ENTERKEY)
        {
            continue;
        }
        else
        {
            char c = static_cast<char>(keypress);
            std::cout << c;
            partial += c;
            // Move the cursor
            cursor.first += 1;
        }
        debug(partial, cursor);
        showPredictions(cursor, tree, partial);
    }
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
    auto wordFound = tree.find("hello");
    std::cout << "Found hello? " << wordFound << std::endl;
    auto outputVec = tree.predict("hel", 1);
    std::cout << "reading from dict..." << std::endl;
    doPredict();
    return 0;
}
