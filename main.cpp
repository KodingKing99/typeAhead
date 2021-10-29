#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
///////////
// @author Nick Sorenson
//////////
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
    std::cout << "loading dictionary..." << std::endl;
    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
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
    // Number of rows
    auto HOWMANY = rlutil::trows() - 10;
    auto HOWMANY2 = rlutil::trows() - 2;
    rlutil::locate(1, 2);
    // clear previous words
    for (int i = 0; i < HOWMANY2; i++)
    {
        std::cout << std::string(40, ' ') << std::endl;
    }

    rlutil::locate(1, 2); // put it back
    if (partial.size() > 0)
    {
        rlutil::locate(1, 3);
        std::cout << "--- prediction ---" << std::endl;
        for (auto word : tree->predict(*split(partial, ' ').rbegin(), HOWMANY))
        {
            std::cout << word << std::endl;
        }
    }
    rlutil::locate(cursor.first, cursor.second);
}
void doPredict()
{
    int ENTERKEY = 10;
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
        showPredictions(cursor, tree, partial);
    }
}
int main()
{
    doPredict();
    return 0;
}
